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

    connect(scanAxis, SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this, SLOT(do_scanAxis_driving_changed(DplSource::Axis::Driving)));

    connect(scanAxis, SIGNAL(resolution_changed(float)),
            this, SLOT(do_encoderX_resolution()));
    connect(static_cast<Encoder*>(scan->encoder_x().data()),
            SIGNAL(resolution_changed(float)),
            this, SLOT(do_encoderX_resolution()));

    connect(scanAxis, SIGNAL(start_changed(float)),
            this, SLOT(do_scanAxis_changed()));

    connect(scanAxis, SIGNAL(resolution_changed(float)),
            this, SLOT(do_scanAxis_changed()));

    do_scanAxis_driving_changed(scan->scan_axis()->driving());
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

void SourcePrivate::do_scanAxis_driving_changed(DplSource::Axis::Driving driving)
{
    m_dma->set_scan_axis_driving(static_cast<Dma::DrivingType>(driving));
}

void SourcePrivate::update_dma_encoder_offset(int qty)
{
    m_dma->set_encoder_offset(qty + 4*sizeof(int));
}

void SourcePrivate::do_encoderX_resolution()
{
    AxisPointer axis = Scan::instance()->scan_axis();
    EncoderPointer enc = Scan::instance()->encoder_x();
    if (axis->driving() == Axis::TIMER) {
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
