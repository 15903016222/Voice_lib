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

    Dma *m_dmaSource;

    Source::Type m_type;

    QList<GroupPointer> m_groups;
};

SourcePrivate::SourcePrivate()
{
    m_interval = 20;
    m_delayFlag = false;
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

void Source::start(int delay)
{
    QWriteLocker l(&d->m_rwlock);
    if (0 == delay) {
        d->m_timer.start();
    } else {
        d->m_delayFlag = true;
        d->m_timer.start(delay);
    }
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

const int Source::MAX_GROUPS = 8;

int Source::groups()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_groups.size();
}

bool Source::add_group(int beamQty, int pointQty)
{
    QWriteLocker l(&d->m_rwlock);
    if (d->m_groups.size() >= MAX_GROUPS) {
        return false;
    }
    d->m_groups.append(GroupPointer(new Group(beamQty, pointQty)));
    return true;
}

bool Source::remove_group(int index)
{
    QWriteLocker l(&d->m_rwlock);
    if (d->m_groups.isEmpty()
            || index >= d->m_groups.size() ) {
        return false;
    }
    d->m_groups.removeAt(index);
    return true;
}

const GroupPointer &Source::get_group(int index)
{
    QReadLocker l(&d->m_rwlock);
    return d->m_groups[index];
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

void Source::update()
{
    if ( ! d->m_dmaSource->is_completed() ) {
        return;
    }

    d->m_dmaSource->clean_completed();

    const char * data = d->m_dmaSource->get_data_buffer();

    int offset = 0;

    d->m_rwlock.lockForWrite();

    if (d->m_delayFlag) {
        d->m_delayFlag = false;
        d->m_timer.setInterval(d->m_interval);
        d->m_rwlock.unlock();
        return;
    }

    for (int i = 0; i < d->m_groups.size(); ++i) {
        d->m_groups[i]->set_raw_data(data+offset);
        offset += d->m_groups[i]->size();
    }

    d->m_rwlock.unlock();

    emit data_event();
}

}
