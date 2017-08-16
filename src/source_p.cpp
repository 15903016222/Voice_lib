#include "source_p.h"

namespace DplSource {

SourcePrivate::SourcePrivate() :
    m_interval(20),
    m_delayFlag(false),
    m_type(Source::DMA),
    m_dma(Dma::instance())
{
    m_timer.setInterval(m_interval);
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
    m_frameSize = offset/1024 * 1024;
}

}
