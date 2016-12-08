#include "beam_source.h"

namespace DplSource {

struct BeamMeasureSource
{
    /* 波型计数器 */
    quint32 focallaw        : 13;   /* 0-12  波型对应聚焦法则的数值 */
    quint32 beamIndex       : 13;   /* 13-25 设置聚焦法则后开始计数的波型数 */
    quint32 gateStatus      : 6;    /* 26-31 闸门状态 */

    /* Gate A */
    quint32 gateAPosition   : 20;   /* 0-19  闸门位置 */
    quint32 gateAHeight     : 12;   /* 20-31 闸门高度 */

    /* Gate B */
    quint32 gateBPosition   : 20;   /* 0-19  闸门位置 */
    quint32 gateBHeight     : 12;   /* 20-31 闸门高度 */

    /* Gate I */
    quint32 gateIPosition   : 20;   /* 0-19  闸门位置 */
    quint32 gateIHeight     : 12;   /* 20-31 闸门高度 */

    int encoderX;   /* 编码器X */
    int encoderY;   /* 编码器Y */

    int res0;       /* 保留 */

    int res1;
};

class BeamSourcePrivate
{
public:
    BeamSourcePrivate();

    const char *m_rawData;
    BeamMeasureSource m_measure;
    int m_pointQty;
};

BeamSourcePrivate::BeamSourcePrivate()
{
    m_rawData = NULL;
    m_pointQty = 0;
    ::memset(&m_measure, 0, sizeof(BeamMeasureSource));
}

BeamSource::BeamSource()
    : d(new BeamSourcePrivate())
{
}

BeamSource::~BeamSource()
{
    delete d;
}

void BeamSource::set_raw_data(const char *data, int pointNum)
{
    if (pointNum == 0 || data == NULL) {
        return;
    }

    d->m_rawData = data;
    d->m_pointQty = pointNum;
    ::memcpy(&d->m_measure, data+pointNum, sizeof(BeamMeasureSource));
}

bool BeamSource::has_data()
{
    return (d->m_rawData != NULL);
}

void BeamSource::clean()
{
    d->m_rawData = NULL;
    d->m_pointQty = 0;
    ::memset(&d->m_measure, 0, sizeof(BeamMeasureSource));
}

bool BeamSource::get_wave(QByteArray &wave)
{
    if (d->m_rawData == NULL) {
        return false;
    }
    wave.clear();
    wave = QByteArray::fromRawData(d->m_rawData, d->m_pointQty);
    return (wave.size() == d->m_pointQty);
}

int BeamSource::point_qty()
{
    return d->m_pointQty;
}

int BeamSource::index()
{
    return d->m_measure.beamIndex;
}

int BeamSource::gate_a_height()
{
    return d->m_measure.gateAHeight;
}

int BeamSource::gate_a_position()
{
    return d->m_measure.gateAPosition;
}

int BeamSource::gate_b_height()
{
    return d->m_measure.gateBHeight;
}

int BeamSource::gate_b_position()
{
    return d->m_measure.gateBPosition;
}

int BeamSource::gate_i_height()
{
    return d->m_measure.gateIHeight;
}

int BeamSource::gate_i_position()
{
    return d->m_measure.gateIPosition;
}

int BeamSource::encoder_x()
{
    return d->m_measure.encoderX;
}

int BeamSource::encoder_y()
{
    return d->m_measure.encoderY;
}

}
