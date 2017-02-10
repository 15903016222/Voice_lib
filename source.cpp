#include "source.h"
#include "dma.h"

#include <QTimer>
#include <QReadWriteLock>

namespace DplSource {

class SourcePrivate
{
public:
    SourcePrivate();

    QReadWriteLock m_rwlock;

    QTimer m_timer;
    int m_interval;
    bool m_delayFlag;
    Source::Type m_type;

    Dma *m_dmaSource;
};

SourcePrivate::SourcePrivate()
{
    m_interval  = 20;
    m_delayFlag = false;
    m_type      = Source::DMA;

    m_timer.setInterval(m_interval);

    m_dmaSource = Dma::get_instance();
}

/* Source */
QMutex Source::m_mutex;
Source *Source::m_source = NULL;

void Source::set_type(Source::Type type)
{
    QWriteLocker l(&d->m_rwlock);
    d->m_type = type;
}

int Source::interval()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_interval;
}

void Source::set_interval(unsigned int interval)
{
    QWriteLocker l(&d->m_rwlock);
    d->m_interval = interval;
    d->m_timer.setInterval(d->m_interval);
}

void Source::stop()
{
    QWriteLocker l(&d->m_rwlock);
    d->m_timer.stop();
}

bool Source::is_running()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_timer.isActive();
}

void Source::start()
{
    QWriteLocker l(&d->m_rwlock);
    d->m_timer.start();
}

Source *Source::get_instance()
{
    QMutexLocker locker(&m_mutex);
    if(m_source == NULL) {
        m_source= new Source();
    }
    return m_source;
}

void Source::destroyed()
{
    QMutexLocker locker(&m_mutex);
    if(m_source != NULL) {
        delete m_source;
        m_source = NULL;
    }
}

void Source::restart()
{
    d->m_delayFlag = true;
    d->m_timer.start(200);
}

Source::Source()
    : d(new SourcePrivate())
{
    connect(&d->m_timer, SIGNAL(timeout()), this, SLOT(update()));
}

Source::~Source()
{
    delete d;
}

void Source::update_dma()
{
    if ( ! d->m_dmaSource->is_completed() ) {
        return;
    }

    d->m_dmaSource->clean_completed();

    emit data_event(d->m_dmaSource->get_data_buffer());

}

void Source::update()
{
    Type type;

    {
        QWriteLocker l(&d->m_rwlock);
        type = d->m_type;

        if (d->m_delayFlag) {
            d->m_delayFlag = false;
            d->m_timer.setInterval(d->m_interval);
            return;
        }

    }

    if (DMA == type) {
        update_dma();
    }

}

}
