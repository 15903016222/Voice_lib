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
    BeamsPrivate(int beamQty, int pointQty, const char *data) :
        m_rawData(data),
        m_beamQty(beamQty),
        m_pointQty(pointQty),
        m_curIndex(0),
        m_rf(false) {}

    /* Attribution */
    const char *m_rawData;
    int m_beamQty;
    int m_pointQty;
    int m_curIndex;
    bool m_rf;
};

Beams::Beams(int beamQty, int pointQty, const char *data) :
    d(new BeamsPrivate(beamQty, pointQty, data))
{

}

Beams::~Beams()
{
    delete d;
}

const BeamPointer Beams::get(int beamNo) const
{
    if (beamNo >= d->m_beamQty
            || d->m_rawData == NULL) {
        return BeamPointer();
    }

    BeamPointer beamPtr = BeamPointer(new Beam);
    beamPtr->set_raw_data(d->m_rawData + beamNo*(d->m_pointQty + Beam::MEASURE_SIZE), d->m_pointQty, d->m_rf);

    return beamPtr;
}

void Beams::set_raw_data(const char *data)
{
    d->m_rawData = data;
}

int Beams::beam_qty() const
{
    return d->m_beamQty;
}

int Beams::point_qty() const
{
    return d->m_pointQty;
}

int Beams::size() const
{
    return (d->m_beamQty)*(d->m_pointQty + Beam::MEASURE_SIZE);
}

bool Beams::rf() const
{
    return d->m_rf;
}

void Beams::set_rf(bool flag)
{
    d->m_rf = flag;
}

const char *Beams::raw_data() const
{
    return d->m_rawData;
}

}
