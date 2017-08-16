/**
 * @file source.cpp
 * @brief 数据源类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-18
 */

#include "source_p.h"

namespace DplSource {

/* Source */
Source *Source::instance()
{
    static Source *ins = new Source();
    return ins;
}

bool Source::register_group(int grp, int beamQty, int pointQty)
{
    Q_D(Source);
    if (grp < MAX_GROUP && !d->m_groups[grp].valid) {
        d->m_groups[grp].valid = true;
        d->m_groups[grp].beamQty = beamQty;
        d->m_groups[grp].pointQty = pointQty;
        d->update_offset();
        return true;
    }
    return false;
}

bool Source::unregister_group(int grp)
{
    Q_D(Source);
    if (grp < MAX_GROUP && d->m_groups[grp].valid) {
        d->m_groups[grp].valid = false;
        return false;
    }
    return true;
}

bool Source::edit_group(int grp, int beamQty, int pointQty)
{
    Q_D(Source);
    if (grp < MAX_GROUP && d->m_groups[grp].valid) {
        d->m_groups[grp].beamQty = beamQty;
        d->m_groups[grp].pointQty = pointQty;
        d->refresh_offset();
        return true;
    }
    return false;
}

Source::Type Source::type() const
{
    Q_D(const Source);
    QReadLocker l(&d->m_rwlock);
    return d->m_type;
}

void Source::set_type(Source::Type type)
{
    Q_D(Source);
    QWriteLocker l(&d->m_rwlock);
    d->m_type = type;
}

int Source::interval() const
{
    Q_D(const Source);
    QReadLocker l(&d->m_rwlock);
    return d->m_interval;
}

void Source::set_interval(unsigned int interval)
{
    Q_D(Source);
    QWriteLocker l(&d->m_rwlock);
    d->m_interval = interval;
    d->m_timer.setInterval(d->m_interval);
}

void Source::stop()
{
    Q_D(Source);
    QWriteLocker l(&d->m_rwlock);
    d->m_timer.stop();
}

bool Source::is_running() const
{
    Q_D(const Source);
    QReadLocker l(&d->m_rwlock);
    return d->m_timer.isActive();
}

void Source::start()
{
    Q_D(Source);
    QWriteLocker l(&d->m_rwlock);
    d->m_timer.start();
}

void Source::restart()
{
    Q_D(Source);

    QWriteLocker l(&d->m_rwlock);
    if (DMA == d->m_type) {
        d->m_dma->set_scan_timmer_counter(0);
        d->m_dma->set_scan_timmer_circled(0);
    }

    d->m_delayFlag = true;
    d->m_timer.start(200);
}

Source::Source()
    : d_ptr(new SourcePrivate(this))
{
    connect(&d_ptr->m_timer, SIGNAL(timeout()), this, SLOT(update()));
}

Source::~Source()
{
    delete d_ptr;
}

void Source::update()
{
    Q_D(Source);
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
        d->update_current_data();
    }
}

}
