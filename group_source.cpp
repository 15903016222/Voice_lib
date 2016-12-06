#include "group_source.h"

namespace DplSource {

class GroupSourcePrivate
{
public:
    GroupSourcePrivate();
    const char *m_rawData;
    int m_beamNum;
    int m_beamSize;
    int m_pointNum;
};

GroupSourcePrivate::GroupSourcePrivate()
{
    m_rawData = NULL;
    m_beamNum = 0;
    m_beamSize = 0;
    m_pointNum = 0;
}

GroupSource::GroupSource(int beamNum, int pointNum)
    :d(new GroupSourcePrivate())
{
    d->m_beamNum = beamNum;
    d->m_beamSize = pointNum + 32;
    d->m_pointNum = pointNum;
}

GroupSource::~GroupSource()
{
    delete d;
}

void GroupSource::set_raw_data(const char *data)
{
    d->m_rawData = data;
}

void GroupSource::set_beam_number(int number)
{
    d->m_beamNum = number;
}

int GroupSource::beam_number()
{
    return d->m_beamNum;
}

void GroupSource::set_point_number(int number)
{
    d->m_pointNum = number;
    d->m_beamSize = number + 32;
}

int GroupSource::point_number()
{
    return d->m_pointNum;
}

const bool GroupSource::get_beam(int beamNo, BeamSource &beam) const
{
    if (beamNo >= d->m_beamNum
            || d->m_rawData == NULL) {
        return false;
    }
    beam.set_raw_data(d->m_rawData+beamNo*d->m_beamSize, d->m_beamSize);
    return true;
}

}
