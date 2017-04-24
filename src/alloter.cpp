/**
 * @file alloter.cpp
 * @brief 分配器，分配各BeamGroup的数据资源
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2017-02-10
 */
#include "alloter.h"
#include "source.h"
#include "dma.h"

namespace DplSource {

Alloter *Alloter::instance()
{
    static Alloter *ins = new Alloter();
    return ins;
}

void Alloter::add(BeamGroup *beams)
{
    {
        QWriteLocker l(&m_rwlock);
        m_beamGroups.append(beams);
        connect(beams, SIGNAL(beam_qty_changed(int)), this, SLOT(set_dma_frame_count()));
        connect(beams, SIGNAL(point_qty_changed(int)), this, SLOT(set_dma_frame_count()));
        if (m_beamGroups.size() == 1) {
            connect(beams, SIGNAL(point_qty_changed(int)),
                    this, SLOT(set_dma_encoder_offset(int)));
            set_dma_encoder_offset(beams->point_qty());
        }
    }
    set_dma_frame_count();
}

void Alloter::remove(BeamGroup *beams)
{
    {
        QWriteLocker l(&m_rwlock);
        m_beamGroups.removeAll(beams);
    }
    set_dma_frame_count();
}

void Alloter::do_data_event(const char *data)
{
    int offset = 0;
    QReadLocker l(&m_rwlock);
    for (int i = 0; i < m_beamGroups.size(); ++i) {
        m_beamGroups[i]->set_raw_data(data + offset);
        offset += m_beamGroups[i]->size();
    }
}

void Alloter::set_dma_driving_type(const DrivingPointer &drivingPtr)
{
    Dma *dma = Dma::instance();

    if (dma != NULL) {
        return;
    }

    if (drivingPtr->type() == Driving::TIMER) {
        dma->set_driving_type(Dma::TIMER);
    } else {
        EncoderPointer enc = drivingPtr.staticCast<Encoder>();

        if (enc->index() == 1) {
            dma->set_driving_type(Dma::ENCODER1);
        } else if (enc->index() == 2) {
            dma->set_driving_type(Dma::ENCODER2);
        }
        set_dma_steps_resolution();
        connect(static_cast<Encoder*>(enc.data()), SIGNAL(resolution_changed(float)),
                this, SLOT(set_dma_steps_resolution()));
    }
}

void Alloter::set_dma_frame_count()
{
    int size = 0;
    for (int i = 0; i < m_beamGroups.size(); ++i) {
        size += m_beamGroups[i]->size();
    }

    Dma *dma = Dma::instance();
    if (dma) {
        int cnt = size / dma->frame_size();
        if( size % dma->frame_size() ) {
            dma->set_frame_count(cnt + 1);
        } else {
            dma->set_frame_count(cnt);
        }
    }
}

void Alloter::set_dma_encoder_offset(int qty)
{
    Axis *axis = Scan::instance()->scan_axis();
    if (axis->driving()->type() == Driving::TIMER) {
        return;
    }

    EncoderPointer enc = axis->driving().staticCast<Encoder>();
    if (enc->index() == 1) {
        Dma::instance()->set_encoder_offset(qty+4*sizeof(int));
    } else {
        Dma::instance()->set_encoder_offset(qty+5*sizeof(int));
    }
}

void Alloter::set_dma_steps_resolution()
{
    Axis *scanAxis = Scan::instance()->scan_axis();
    if (scanAxis->driving()->type() == Driving::TIMER) {
        return;
    }

    EncoderPointer enc = scanAxis->driving().staticCast<Encoder>();
    Dma::instance()->set_steps_resolution(scanAxis->resolution() * enc->resolution());
}

void Alloter::set_dma_start_offset()
{
    Axis *scanAxis = Scan::instance()->scan_axis();
    Dma::instance()->set_start_offset(-(scanAxis->start()/scanAxis->resolution()));
}

Alloter::Alloter(QObject *parent) :
    QObject(parent)
{
    Source *source = Source::instance();
    connect(source, SIGNAL(data_event(const char*)),
            this, SLOT(do_data_event(const char*)));

    Axis *scanAxis = Scan::instance()->scan_axis();
    connect(scanAxis, SIGNAL(resolution_changed(float)),
            this, SLOT(set_dma_steps_resolution()));
    connect(scanAxis, SIGNAL(driving_changed(DrivingPointer)),
            this, SLOT(set_dma_driving_type(DrivingPointer)));
    connect(scanAxis, SIGNAL(start_changed(float)),
            this, SLOT(set_dma_start_offset()));
    connect(scanAxis, SIGNAL(resolution_changed(float)),
            this, SLOT(set_dma_start_offset()));

    set_dma_driving_type(scanAxis->driving());
    set_dma_start_offset();
}

}
