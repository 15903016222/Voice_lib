/**
 * @file beam_group.cpp
 * @brief Beam组类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-18
 */
#include "alloter.h"

#include <QReadWriteLock>

namespace DplSource {

class BeamsPrivate
{
public:
    BeamsPrivate() :
        m_rawData(NULL),
        m_beamQty(0),
        m_pointQty(0),
        m_curIndex(0),
        m_rf(false) {}

    /* Attribution */
    QReadWriteLock m_rwlock;
    const char *m_rawData;
    int m_beamQty;
    int m_pointQty;
    int m_curIndex;
    bool m_rf;
};

Beams::Beams(QObject *parent) :
    QObject(parent),
    d(new BeamsPrivate)
{
    Alloter::instance()->add(this);
}

Beams::~Beams()
{
    Alloter::instance()->remove(this);
}

const BeamPointer Beams::get(int beamNo) const
{
    QReadLocker l(&d->m_rwlock);

    if (beamNo >= d->m_beamQty
            || d->m_rawData == NULL) {
        return BeamPointer();
    }

    BeamPointer beamPtr = BeamPointer(new Beam);
    beamPtr->set_raw_data(d->m_rawData + beamNo*(d->m_pointQty + Beam::MEASURE_SIZE), d->m_pointQty, d->m_rf);

    return beamPtr;
}

BeamPointer Beams::current_beam() const
{
    return get(d->m_curIndex);
}

void Beams::set_current_beam_index(int index)
{
    QWriteLocker l(&d->m_rwlock);
    d->m_curIndex = index;
}

void Beams::set_raw_data(const char *data)
{
    {
        QWriteLocker l(&d->m_rwlock);
        d->m_rawData = data;
    }
    emit data_event();
}

void Beams::set_beam_qty(int qty)
{
    {
        QWriteLocker l(&d->m_rwlock);
        d->m_beamQty = qty;
    }
    emit beam_qty_changed(qty);
}

void Beams::set_point_qty(int qty)
{
    {
        QWriteLocker l(&d->m_rwlock);
        d->m_pointQty = qty;
    }
    emit point_qty_changed(qty);
}

int Beams::beam_qty() const
{
    QReadLocker l(&d->m_rwlock);
    return d->m_beamQty;
}

int Beams::point_qty() const
{
    QReadLocker l(&d->m_rwlock);
    return d->m_pointQty;
}

int Beams::size() const
{
    QReadLocker l(&d->m_rwlock);
    return (d->m_beamQty)*(d->m_pointQty + Beam::MEASURE_SIZE);
}

bool Beams::rf() const
{
    QReadLocker l(&d->m_rwlock);
    return d->m_rf;
}

void Beams::set_rf(bool flag)
{
    QWriteLocker l(&d->m_rwlock);
    d->m_rf = flag;
}

}
