#include "group.h"

namespace DplSource {

class GroupPrivate
{
public:
    GroupPrivate();
    const char *m_rawData;
    int m_beamQty;
    int m_beamSize;
    int m_pointQty;
};

GroupPrivate::GroupPrivate()
{
    m_rawData = NULL;
    m_beamQty = 0;
    m_beamSize = 0;
    m_pointQty = 0;
}

Group::Group(int beamNum, int pointNum)
    :d(new GroupPrivate())
{
    d->m_beamQty = beamNum;
    d->m_beamSize = pointNum + 32;
    d->m_pointQty = pointNum;
}

Group::~Group()
{
    delete d;
}

void Group::set_raw_data(const char *data)
{
    d->m_rawData = data;
}

void Group::set_beam_qty(int qty)
{
    d->m_beamQty = qty;
}

int Group::beam_qty()
{
    return d->m_beamQty;
}

void Group::set_point_qty(int qty)
{
    d->m_pointQty = qty;
    d->m_beamSize = qty + 32;
}

int Group::point_qty()
{
    return d->m_pointQty;
}

int Group::size()
{
    return (d->m_beamSize * d->m_beamQty);
}

bool Group::get_beam(int beamNo, Beam &beam) const
{
    if (beamNo >= d->m_beamQty
            || d->m_rawData == NULL) {
        return false;
    }
    beam.set_raw_data(d->m_rawData+beamNo*d->m_beamSize, d->m_pointQty);
    return true;
}

}
