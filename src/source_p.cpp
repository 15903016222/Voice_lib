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
    Scan::instance();
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
        qDebug("%s[%d]: ",__func__, __LINE__);
        m_curData = m_dma->read_data();
        emit q_ptr->data_event();
        qDebug("%s[%d]: ",__func__, __LINE__);
        QThread::msleep(m_interval);
    }
}

}
