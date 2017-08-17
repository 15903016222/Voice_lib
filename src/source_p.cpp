#include "source_p.h"
#include "scan.h"

namespace DplSource {

SourcePrivate::SourcePrivate(Source *source) : QThread(),
    q_ptr(source),
    m_interval(20),
    m_type(Source::DMA),
    m_dma(Dma::instance()),
    m_data(Dma::instance()->get_store_buffer())
{    
    Axis *scanAxis = Scan::instance()->scan_axis();
    connect(scanAxis, SIGNAL(resolution_changed(float)),
            this, SLOT(update_dma_steps_resolution()));
    connect(scanAxis, SIGNAL(driving_changed(DrivingPointer)),
            this, SLOT(update_dma_driving_type(DrivingPointer)));
    connect(scanAxis, SIGNAL(start_changed(float)),
            this, SLOT(update_dma_start_offset()));
    connect(scanAxis, SIGNAL(resolution_changed(float)),
            this, SLOT(update_dma_start_offset()));

    update_dma_driving_type(scanAxis->driving());
    update_dma_start_offset();
}

void SourcePrivate::update_current_data()
{
    m_curData = m_dma->read_data();
}

void SourcePrivate::update_offset()
{
    int offset = 0;
    for (int i = 0; i < MAX_GROUP; ++i) {
        if (m_groups[i].valid) {
            m_groups[i].offset = offset;
            offset += m_groups[i].beamQty*(m_groups[i].pointQty + Beam::MEASURE_SIZE);
        }
    }

    Dma *dma = Dma::instance();
    int cnt = offset / dma->frame_size();
    if (offset % dma->frame_size()) {
        dma->set_frame_count(cnt + 1);
    } else {
        dma->set_frame_count(cnt);
    }
    m_frameSize = cnt * dma->frame_size();
}

void SourcePrivate::update_dma_driving_type(const DrivingPointer &driving)
{
    if (driving->type() == Driving::TIMER) {
        m_dma->set_driving_type(Dma::TIMER);
    } else {
        EncoderPointer enc = driving.staticCast<Encoder>();

        if (enc->index() == 1) {
            m_dma->set_driving_type(Dma::ENCODER1);
        } else if (enc->index() == 2) {
            m_dma->set_driving_type(Dma::ENCODER2);
        }
        update_dma_steps_resolution();
        connect(static_cast<Encoder*>(enc.data()), SIGNAL(resolution_changed(float)),
                this, SLOT(update_dma_steps_resolution()));
    }
}

void SourcePrivate::update_dma_encoder_offset(int qty)
{
    Axis *axis = Scan::instance()->scan_axis();
    if (axis->driving()->type() == Driving::TIMER) {
        return;
    }

    EncoderPointer enc = axis->driving().staticCast<Encoder>();
    if (enc->index() == 1) {
        m_dma->set_encoder_offset(qty + 4*sizeof(int));
    } else {
        m_dma->set_encoder_offset(qty + 5*sizeof(int));
    }
}

void SourcePrivate::update_dma_steps_resolution()
{
    Axis *axis = Scan::instance()->scan_axis();
    if (axis->driving()->type() == Driving::TIMER) {
        return;
    }
    EncoderPointer enc = axis->driving().staticCast<Encoder>();
    m_dma->set_steps_resolution(axis->resolution() * enc->resolution());
}

void SourcePrivate::update_dma_start_offset()
{
    Axis *axis = Scan::instance()->scan_axis();
    m_dma->set_start_offset(-(axis->start()/axis->resolution()));
}

void SourcePrivate::run()
{
    while (true) {
        m_curData = m_dma->read_data();
        if (m_curData) {
            emit q_ptr->data_event();
        }
        QThread::msleep(m_interval);
    }
}

}
