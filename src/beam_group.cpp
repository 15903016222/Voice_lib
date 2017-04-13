#include "beam_group.h"
#include "alloter.h"

#include <QReadWriteLock>

namespace DplSource {

class BeamGroupPrivate
{
public:
    BeamGroupPrivate();

    /* Attribution */
    QReadWriteLock m_rwlock;
    const char *m_rawData;
    int m_beamQty;
    int m_pointQty;
};

BeamGroupPrivate::BeamGroupPrivate()
{
    m_rawData = NULL;
    m_beamQty = 0;
    m_pointQty = 0;
}


BeamGroup::BeamGroup(QObject *parent) :
    QObject(parent),
    d(new BeamGroupPrivate)
{
    Alloter::instance()->add(this);
}

BeamGroup::~BeamGroup()
{
    Alloter::instance()->remove(this);
}

const BeamPointer BeamGroup::get(int beamNo)
{
    QReadLocker l(&d->m_rwlock);

    if (beamNo >= d->m_beamQty
            || d->m_rawData == NULL) {
        return BeamPointer();
    }

    BeamPointer beamPtr = BeamPointer(new Beam);
    beamPtr->set_raw_data(d->m_rawData + beamNo*(d->m_pointQty + Beam::MEASURE_SIZE), d->m_pointQty);

    return beamPtr;
}

void BeamGroup::set_raw_data(const char *data)
{
    {
        QWriteLocker l(&d->m_rwlock);
        d->m_rawData = data;
    }
    emit data_event();
}

void BeamGroup::set_beam_qty(int qty)
{
    {
        QWriteLocker l(&d->m_rwlock);
        d->m_beamQty = qty;
    }
    emit beam_qty_changed(qty);
}

void BeamGroup::set_point_qty(int qty)
{
    {
        QWriteLocker l(&d->m_rwlock);
        d->m_pointQty = qty;
    }
    emit point_qty_changed(qty);
}

int BeamGroup::beam_qty() const
{
    QReadLocker l(&d->m_rwlock);
    return d->m_beamQty;
}

int BeamGroup::point_qty() const
{
    QReadLocker l(&d->m_rwlock);
    return d->m_pointQty;
}

int BeamGroup::size() const
{
    QReadLocker l(&d->m_rwlock);
    return (d->m_beamQty)*(d->m_pointQty + Beam::MEASURE_SIZE);
}

}
