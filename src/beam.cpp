/**
 * @file beam.cpp
 * @brief beam类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-18
 */

#include "beam.h"

namespace DplSource {

struct GateData {
    quint32 position    : 20;   // 0-19 闸门检测数据的位置
    quint32 height      : 12;   // 20-31 闸门检测数据的高度
};

struct GateRFData {
    quint32 positon     : 16;   // 0-15 射频模式中闸门检测数据的位置
    quint32 height      : 16;   // 16-31 射频模式中闸门检测数据的高度
};

#pragma pack(1)
struct Measure
{
    /* 波型计数器 */
    quint32 focallaw        : 13;   /* 0-12  波型对应聚焦法则的数值 */
    quint32 beamIndex       : 13;   /* 13-25 设置聚焦法则后开始计数的波型数 */
    quint32 gateStatus      : 6;    /* 26-31 闸门状态 */

    /* Gate A */
    union {
        GateData gateA;
        GateRFData gateARF;
    };

    /* Gate B */
    union {
        GateData gateB;
        GateRFData gateBRF;
    };

    /* Gate I */
    union {
        GateData gateI;
        GateRFData gateIRF;
    };

    int encoderX;   /* 编码器X */
    int encoderY;   /* 编码器Y */

    int res0;       /* 保留 */

    int res1;       /* 保留 */
};
#pragma pack()

class BeamPrivate
{
public:
    BeamPrivate() :
        m_rawData(NULL),
        m_measure(NULL),
        m_pointQty(0) {}

    /* Attribution */
    const char *m_rawData;
    const Measure *m_measure;
    int m_pointQty;
};

/* Class Beam */

const int Beam::MEASURE_SIZE;
const float Beam::MAX_GATE_HEIGHT = 4095.0;

Beam::Beam()
    : d(new BeamPrivate())
{
}

Beam::~Beam()
{
    delete d;
}

void Beam::set_raw_data(const char *data, int pointNum)
{
    if (pointNum == 0 || data == NULL) {
        return;
    }

    d->m_rawData = data;
    d->m_pointQty = pointNum;
    d->m_measure = (const Measure *)(data + pointNum);
}

bool Beam::has_data() const
{
    return (d->m_rawData != NULL);
}

void Beam::clean()
{
    d->m_rawData = NULL;
    d->m_measure = NULL;
    d->m_pointQty = 0;
}

QByteArray Beam::get_wave() const
{
    if (d->m_rawData == NULL) {
        return NULL;
    }
    return QByteArray::fromRawData(d->m_rawData, d->m_pointQty);
}

int Beam::point_qty() const
{
    return d->m_pointQty;
}

int Beam::index() const
{
    return d->m_measure->beamIndex;
}

int Beam::gate_a_height() const
{
    return d->m_measure->gateA.height;
}

int Beam::gate_a_position() const
{
    return d->m_measure->gateA.position;
}

int Beam::gate_b_height() const
{
    return d->m_measure->gateB.height;
}

int Beam::gate_b_position() const
{
    return d->m_measure->gateB.position;
}

int Beam::gate_i_height() const
{
    return d->m_measure->gateI.height;
}

int Beam::gate_i_position() const
{
    return d->m_measure->gateI.position;
}

int Beam::encoder_x() const
{
    return d->m_measure->encoderX;
}

int Beam::encoder_y() const
{
    return d->m_measure->encoderY;
}

float Beam::gate_peak(Beam::GateType gate, bool rf) const
{
    float peak = 0.0;
    switch (gate) {
    case GATE_A:
        if (rf) {
            peak = d->m_measure->gateARF.height;
        } else {
            peak = d->m_measure->gateA.height;
        }
        break;
    case GATE_B:
        if (rf) {
            peak = d->m_measure->gateBRF.height;
        } else {
            peak = d->m_measure->gateB.height;
        }
        break;
    case GATE_I:
    default:
        if (rf) {
            peak = d->m_measure->gateIRF.height;
        } else {
            peak = d->m_measure->gateI.height;
        }
        break;
    }
    if (rf) {
        peak /= (10.24*16);
    } else {
        peak /= 20.47;          // 满屏时200%, peak/(4095/2)*100
    }
    return peak;
}

}
