#include "source.h"
#include "dma.h"

#include <QTimer>
#include <QReadWriteLock>

namespace DplSource {

class SourcePrivate : public QObject
{
    Q_OBJECT
public:
    SourcePrivate(Source *source);

    QReadWriteLock m_rwlock;

    QTimer m_timer;

    Dma *m_dmaSource;

    Source *m_source;

    Source::Type m_type;

    QList<GroupSourcePointer> m_groups;

protected slots:
    void do_timeout_event();
};

SourcePrivate::SourcePrivate(Source *source)
{
    m_source = source;

    m_timer.setInterval(20);

    m_dmaSource = Dma::get_instance();

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(do_timeout_event()));
}

void SourcePrivate::do_timeout_event()
{
    if ( ! m_dmaSource->is_completed() ) {
        return;
    }

    m_dmaSource->clean_completed();

    const char * data = m_dmaSource->get_data_buffer();

    if (data.isEmpty()) {
        return;
    }

    int offset = 0;
    for (int i = 0; i < m_groups.size(); ++i) {
        m_groups[i]->set_raw_data(data+offset);
        offset += m_groups[i]->size();
    }

    emit m_source->data_event();
}

/* Source */
QMutex Source::m_mutex;
Source *Source::m_source = NULL;

void Source::set_type(Source::Type type)
{
    d->m_type = type;
}

void Source::set_interval(unsigned int interval)
{
    QWriteLocker l(&d->m_rwlock);
    d->m_timer.setInterval(interval);
}

void Source::set_freeze(bool flag)
{
    QWriteLocker l(&d->m_rwlock);
    if (flag) {
        d->m_timer.stop();
    } else {
        d->m_timer.start();
    }
}

bool Source::is_freeze()
{
    QReadLocker l(&d->m_rwlock);
    return ! d->m_timer.isActive();
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
    return d->m_groups.size();
}

bool Source::create_group(int beamNum, int pointNum)
{
    if (d->m_groups.size() >= MAX_GROUPS) {
        return false;
    }
    d->m_groups.append(GroupSourcePointer(new GroupSource(beamNum, pointNum)));
    return true;
}

bool Source::remove_group()
{
    if (d->m_groups.size() == 0) {
        return false;
    }
    d->m_groups.removeLast();
    return true;
}

const GroupSourcePointer &Source::get_group(int index)
{
    return d->m_groups[index];
}

Source::Source()
    : d(new SourcePrivate())
{

}

Source::~Source()
{
    delete d;
}

}
