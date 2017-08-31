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
    Scan *scan = Scan::instance();
    Axis *scanAxis = Scan::instance()->scan_axis().data();

    connect(static_cast<Encoder *>(scan->encoder_x().data()),
            SIGNAL(mode_changed(DplSource::Encoder::Mode)),
            this, SLOT(do_encoderX_mode_changed(DplSource::Encoder::Mode)));

    connect(scanAxis, SIGNAL(resolution_changed(float)),
            this, SLOT(do_encoderX_resolution()));
    connect(static_cast<Encoder*>(scan->encoder_x().data()),
            SIGNAL(resolution_changed(float)),
            this, SLOT(do_encoderX_resolution()));

    connect(scanAxis, SIGNAL(start_changed(float)),
            this, SLOT(do_scanAxis_changed()));

    connect(scanAxis, SIGNAL(resolution_changed(float)),
            this, SLOT(do_scanAxis_changed()));

    do_encoderX_mode_changed(scan->encoder_x()->mode());
    do_encoderX_resolution();

    do_scanAxis_changed();
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

void SourcePrivate::do_encoderX_mode_changed(DplSource::Encoder::Mode mode)
{
    if (Encoder::OFF == mode) {
        m_dma->set_scan_axis_driving(Dma::TIMER);
    } else {
        m_dma->set_scan_axis_driving(Dma::ENCODER1);
    }
}

void SourcePrivate::update_dma_encoder_offset(int qty)
{
    EncoderPointer enc = Scan::instance()->encoder_x();

    if (enc->mode() == Encoder::OFF) {
        return;
    }

    m_dma->set_encoder_offset(qty + 4*sizeof(int));
}

void SourcePrivate::do_encoderX_resolution()
{
    AxisPointer axis = Scan::instance()->scan_axis();
    EncoderPointer enc = Scan::instance()->encoder_x();
    if (enc->mode() == Encoder::OFF) {
        return;
    }

    m_dma->set_steps_resolution(axis->resolution() * enc->resolution());
}

void SourcePrivate::do_scanAxis_changed()
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
