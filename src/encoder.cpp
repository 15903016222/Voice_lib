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
    EncoderPrivate() :
        m_enabled(false),
        m_polarity(Encoder::NORMAL),
        m_mode(Encoder::OFF),
        m_resolution(48.0),
        m_origin(0.0)
    {}

    bool m_enabled;
    Encoder::Polarity m_polarity;   // 极性
    Encoder::Mode m_mode;           // 模式
    float m_resolution;             // 分辨率(steps/mm)
    float m_origin;                 // 起点(mm)
};

Encoder::Encoder(QObject *parent) :
    QObject(parent),
    d_ptr(new EncoderPrivate())
{

}

Encoder::~Encoder()
{
    delete d_ptr;
}

bool Encoder::is_enabled() const
{
    Q_D(const Encoder);
    return d->m_enabled;
}

void Encoder::set_enabled(bool enable)
{
    Q_D(Encoder);
    if (d->m_enabled != enable) {
        d->m_enabled = enable;
        emit enabled_changed(enable);
    }
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
