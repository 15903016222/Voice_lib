/**
 * @file beam.cpp
 * @brief beam类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-18
 */

#include "beam.h"

#include <qmath.h>

namespace DplSource {

struct GateData {
    quint32 position    : 20;   // 0-19 闸门检测数据的位置
    quint32 height      : 12;   // 20-31 闸门检测数据的高度
};

#pragma pack(1)
struct Measure
{
    /* 波型计数器 */
    quint32 focallaw        : 13;   // 0-12  波型对应聚焦法则的数值
    quint32 beamIndex       : 13;   // 13-25 设置聚焦法则后开始计数的波型数
    quint32 gateStatus      : 6;    // 26-31 闸门状态

    GateData gate[3];               // Gate A/B/I

    int encoderX;                   // 编码器X
    int encoderY;                   // 编码器Y

    int res0;                       // 保留

    int res1;                       // 保留
};
#pragma pack()

class BeamPrivate
{
public:
    BeamPrivate() :
        m_measure(NULL),
        m_rf(false) {}

    /* Attribution */
    QByteArray m_wave;
    const Measure *m_measure;
    bool m_rf;
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

void Beam::set_raw_data(const char *data, int pointNum, bool rf)
{
    if (pointNum == 0 || data == NULL) {
        return;
    }

    d->m_wave.setRawData(data, pointNum);
    d->m_measure = (const Measure *)(data + pointNum);
    d->m_rf = rf;
}

void Beam::clean()
{
    d->m_measure = NULL;
}

const QByteArray &Beam::wave() const
{
    return d->m_wave;
}

int Beam::point_qty() const
{
    return d->m_wave.size();
}

int Beam::index() const
{
    return d->m_measure->beamIndex;
}

int Beam::encoder_x() const
{
    return d->m_measure->encoderX;
}

int Beam::encoder_y() const
{
    return d->m_measure->encoderY;
}

float Beam::gate_peak(Beam::GateType gate) const
{
    Q_ASSERT( gate >= GATE_A && gate <= GATE_I );
	if ( d->m_rf) {
        return static_cast<qint16>(d->m_measure->gate[gate].height) / 10.24;    // 满屏时200%, peak/((2^12)/4)*100
	} else {
        return d->m_measure->gate[gate].height / 20.47;                         // 满屏时200%, peak/((2^12-1)/2)*100
    }
}

float Beam::gate_minus(Beam::GateType gate, int height)
{
    if (height == 0) {
        height = 1;
    }

    return 20 * log10(gate_peak(gate)/height);
}

int Beam::gate_peak_position(DplSource::Beam::GateType gate)
{
    Q_ASSERT( gate >= GATE_A && gate <= GATE_I );
    return d->m_measure->gate[gate].position;
}


}
