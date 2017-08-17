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
        d->update_offset();
        return true;
    }
    return false;
}

BeamsPointer Source::current_beams(int grp)
{
    Q_D(Source);
    if (grp < MAX_GROUP && d->m_groups[grp].valid) {
        BeamsPointer beams(new Beams(d->m_groups[grp].beamQty,
                                     d->m_groups[grp].pointQty,
                                     d->m_curData + d->m_groups[grp].offset));
        return beams;
    }
    return BeamsPointer();
}

BeamsPointer Source::beams(int grp, int frameIndex)
{
    Q_D(Source);
    if (grp < MAX_GROUP && d->m_groups[frameIndex].valid) {
        BeamsPointer beams(new Beams(d->m_groups[frameIndex].beamQty,
                                     d->m_groups[frameIndex].pointQty,
                                     d->m_data + d->m_frameSize*frameIndex + d->m_groups[frameIndex].offset));
        return beams;
    }
    return BeamsPointer();
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
}

void Source::stop()
{
    Q_D(Source);
}

bool Source::is_running() const
{
    Q_D(const Source);
    return d->isRunning();
}

void Source::start()
{
    Q_D(Source);
    d->start();
}

void Source::restart()
{
    Q_D(Source);

    QWriteLocker l(&d->m_rwlock);
    if (DMA == d->m_type) {
        d->m_dma->set_scan_timmer_counter(0);
        d->m_dma->set_scan_timmer_circled(0);
    }
}

Source::Source()
    : d_ptr(new SourcePrivate(this))
{
}

Source::~Source()
{
    delete d_ptr;
}

}
