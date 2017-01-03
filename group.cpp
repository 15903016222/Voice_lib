#include "group.h"

namespace DplSource {

class GroupPrivate
{
public:
    GroupPrivate();
    const char *m_rawData;
    int m_beamNum;
    int m_beamSize;
    int m_pointNum;
};

GroupPrivate::GroupPrivate()
{
    m_rawData = NULL;
    m_beamNum = 0;
    m_beamSize = 0;
    m_pointNum = 0;
}

Group::Group(int beamNum, int pointNum)
    :d(new GroupPrivate())
{
    d->m_beamNum = beamNum;
    d->m_beamSize = pointNum + 32;
    d->m_pointNum = pointNum;
}

Group::~Group()
{
    delete d;
}

void Group::set_raw_data(const char *data)
{
    d->m_rawData = data;
}

void Group::set_beam_number(int number)
{
    d->m_beamNum = number;
}

int Group::beam_number()
{
    return d->m_beamNum;
}

void Group::set_point_number(int number)
{
    d->m_pointNum = number;
    d->m_beamSize = number + 32;
}

int Group::point_number()
{
    return d->m_pointNum;
}

int Group::size()
{
    return (d->m_beamSize * d->m_beamNum);
}

bool Group::get_beam(int beamNo, Beam &beam) const
{
    if (beamNo >= d->m_beamNum
            || d->m_rawData == NULL) {
        return false;
    }
    beam.set_raw_data(d->m_rawData+beamNo*d->m_beamSize, d->m_pointNum);
    return true;
}

}
