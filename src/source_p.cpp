#include "source_p.h"

namespace DplSource {

SourcePrivate::SourcePrivate(Source *parent) :
    q_ptr(parent),
    m_interval(20),
    m_delayFlag(false),
    m_type(Source::DMA),
    m_dma(Dma::instance())
{
    m_timer.setInterval(m_interval);
}

void SourcePrivate::update_current_data()
{
    Q_Q(Source);
    const char *data = m_dma->read_data();
    if (data == NULL) {
        return;
    }
    emit q->data_event(data);
}

}
