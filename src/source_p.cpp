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
    Axis *scanAxis = Scan::instance()->scan_axis().data();
    connect(scanAxis, SIGNAL(resolution_changed(float)),
            this, SLOT(update_dma_steps_resolution()));
    connect(static_cast<Encoder *>(scanAxis->encoder().data()),
            SIGNAL(mode_changed(DplSource::Encoder::Mode)),
            this, SLOT(update_dma_driving_type(DplSource::Encoder::Mode)));
    connect(scanAxis, SIGNAL(start_changed(float)),
            this, SLOT(update_dma_start_offset()));
    connect(scanAxis, SIGNAL(resolution_changed(float)),
            this, SLOT(update_dma_start_offset()));

    update_dma_driving_type(scanAxis->encoder()->mode());
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
        ++cnt;
    }

    dma->set_frame_count(cnt);

    m_frameSize = cnt * dma->frame_size();
}

void SourcePrivate::update_dma_driving_type(DplSource::Encoder::Mode mode)
{
    if (Encoder::OFF == mode) {
        m_dma->set_driving_type(Dma::TIMER);
    } else {
        EncoderPointer enc = Scan::instance()->scan_axis()->encoder();

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
    AxisPointer axis = Scan::instance()->scan_axis();
    EncoderPointer enc = axis->encoder();

    if (enc->mode() == Encoder::OFF) {
        return;
    }

    if (enc->index() == 1) {
        m_dma->set_encoder_offset(qty + 4*sizeof(int));
    } else {
        m_dma->set_encoder_offset(qty + 5*sizeof(int));
    }
}

void SourcePrivate::update_dma_steps_resolution()
{
    AxisPointer axis = Scan::instance()->scan_axis();
    EncoderPointer enc = axis->encoder();
    if (enc->mode() == Encoder::OFF) {
        return;
    }
    m_dma->set_steps_resolution(axis->resolution() * enc->resolution());
}

void SourcePrivate::update_dma_start_offset()
{
    AxisPointer axis = Scan::instance()->scan_axis();
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
