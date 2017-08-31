/**
 * @file encoder.cpp
 * @brief 编码器
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-18
 */

#include "encoder.h"

namespace DplSource {

class EncoderPrivate
{
public:
    EncoderPrivate(Encoder::Type type) :
        m_type(type),
        m_polarity(Encoder::NORMAL),
        m_mode(Encoder::OFF),
        m_resolution(48.0),
        m_origin(0.0)
    {}

    Encoder::Type m_type;
    Encoder::Polarity m_polarity;   // 极性
    Encoder::Mode m_mode;           // 模式
    float m_resolution;             // 分辨率(steps/mm)
    float m_origin;                 // 起点(mm)
};

Encoder::Encoder(Type type, QObject *parent) :
    QObject(parent),
    d_ptr(new EncoderPrivate(type))
{

}

Encoder::~Encoder()
{
    delete d_ptr;
}

Encoder::Type Encoder::type() const
{
    Q_D(const Encoder);
    return d->m_type;
}

void Encoder::set_type(Type type)
{
    Q_D(Encoder);
    d->m_type = type;
}

Encoder::Polarity Encoder::polarity() const
{
    Q_D(const Encoder);
    return d->m_polarity;
}

void Encoder::set_polarity(Encoder::Polarity val)
{
    Q_D(Encoder);
    d->m_polarity = val;
}

Encoder::Mode Encoder::mode() const
{
    Q_D(const Encoder);
    return d->m_mode;
}

void Encoder::set_mode(Encoder::Mode mode)
{
    Q_D(Encoder);
    if (d->m_mode != mode) {
        d->m_mode = mode;
        emit mode_changed(mode);
    }
}

float Encoder::resolution() const
{
    Q_D(const Encoder);
    return d->m_resolution;
}

void Encoder::set_resolution(float val)
{
    Q_D(Encoder);
    d->m_resolution = val;
    emit resolution_changed(val);
}

float Encoder::origin() const
{
    Q_D(const Encoder);
    return d->m_origin;
}

void Encoder::set_origin(float val)
{
    Q_D(Encoder);
    d->m_origin = val;
}

}
