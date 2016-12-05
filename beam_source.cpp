#include "beam_source.h"

namespace DplSource {

struct BeamSourceCode
{
    /* 波型计数器 */
    quint32 focallaw    : 13;   /* 0-12  波型对应聚焦法则的数值 */
    quint32 beamIndex   : 13;   /* 13-25 设置聚焦法则后开始计数的波型数 */
    quint32 gateStatus  : 6;    /* 26-31 闸门状态 */

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
    const BeamSourceCode *m_code;
    int m_pointQty;
};

BeamSourcePrivate::BeamSourcePrivate()
{
    m_rawData = NULL;
    m_code = NULL;
    m_pointQty = 0;
}

BeamSource::BeamSource(const char *data, int size)
    : d(new BeamSourcePrivate())
{
    if (size <= 32 || data == NULL) {
        return;
    }
    d->m_pointQty = size - 32;
    d->m_rawData = data;
    d->m_code = (BeamSourceCode *)(data + pointQty);
}

void BeamSource::set_raw_data(const char *data, int size)
{
    if (size <= 32 || data == NULL) {
        return;
    }

    d->m_rawData = data;
    d->m_code = (BeamSourceCode *)(data + d->m_pointQty);
    d->m_pointQty = size - 32;
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
    return d->m_code->beamIndex;
}

int BeamSource::gate_a_height()
{
    return d->m_code->gateAHeight;
}

int BeamSource::gate_a_position()
{
    return d->m_code->gateAPosition;
}

int BeamSource::gate_b_height()
{
    return d->m_code->gateBHeight;
}

int BeamSource::gate_b_position()
{
    return d->m_code->gateBPosition;
}

int BeamSource::gate_i_height()
{
    return d->m_code->gateIHeight;
}

int BeamSource::gate_i_position()
{
    return d->m_code->gateIPosition;
}

int BeamSource::encoder_x()
{
    return d->m_code->encoderX;
}

int BeamSource::encoder_y()
{
    return d->m_code->encoderY;
}

}
