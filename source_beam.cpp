#include "source_beam.h"

namespace DplSource {

struct SourceBeamCode
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

class SourceBeamPrivate
{
public:
    SourceBeamPrivate();

    const char *m_rawData;
    const SourceBeamCode *m_code;
    int m_pointQty;
};

SourceBeamPrivate::SourceBeamPrivate()
{
    m_rawData = NULL;
    m_code = NULL;
    m_pointQty = 0;
}

SourceBeam::SourceBeam(const char *data, int size)
    : d(new SourceBeamPrivate())
{
    if (size <= 32 || data == NULL) {
        return;
    }
    d->m_pointQty = size - 32;
    d->m_rawData = data;
    d->m_code = (SourceBeamCode *)(data + pointQty);
}

void SourceBeam::set_raw_data(const char *data, int size)
{
    if (size <= 32 || data == NULL) {
        return;
    }

    d->m_rawData = data;
    d->m_code = (SourceBeamCode *)(data + d->m_pointQty);
    d->m_pointQty = size - 32;
}

bool SourceBeam::get_wave(QByteArray &wave)
{
    if (d->m_rawData == NULL) {
        return false;
    }
    wave.clear();
    wave = QByteArray::fromRawData(d->m_rawData, d->m_pointQty);
    return (wave.size() == d->m_pointQty);
}

int SourceBeam::point_qty()
{
    return d->m_pointQty;
}

int SourceBeam::index()
{
    return d->m_code->beamIndex;
}

int SourceBeam::gate_a_height()
{
    return d->m_code->gateAHeight;
}

int SourceBeam::gate_a_position()
{
    return d->m_code->gateAPosition;
}

int SourceBeam::gate_b_height()
{
    return d->m_code->gateBHeight;
}

int SourceBeam::gate_b_position()
{
    return d->m_code->gateBPosition;
}

int SourceBeam::gate_i_height()
{
    return d->m_code->gateIHeight;
}

int SourceBeam::gate_i_position()
{
    return d->m_code->gateIPosition;
}

int SourceBeam::encoder_x()
{
    return d->m_code->encoderX;
}

int SourceBeam::encoder_y()
{
    return d->m_code->encoderY;
}

}
