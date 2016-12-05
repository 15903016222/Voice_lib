#include "source_group.h"

namespace DplSource {

class SourceGroupPrivate
{
public:
    SourceGroupPrivate();
    const char *m_rawData;
    int m_beamSize;
    int m_beamNum;
};

SourceGroupPrivate::SourceGroupPrivate()
{
    m_rawData = NULL;
    m_beamNum = 0;
    m_beamSize = 0;
}

SourceGroup::SourceGroup(const char *rawData, int size, int beamNum)
    :d(new SourceGroupPrivate())
{
    if (rawData == NULL) {
        return;
    }
    d->m_rawData = rawData;
    d->m_beamNum = beamNum;

}

void SourceGroup::set_raw_data(const char *data)
{
    d->m_rawData = data;
}

const bool SourceGroup::get_beam(int index, SourceBeam &beam) const
{
    if (index >= d->m_beamNum) {
        return false;
    }
    beam.set_raw_data(m_rawData+index*d->m_beamSize, d->m_beamSize);
    return true;
}

}
