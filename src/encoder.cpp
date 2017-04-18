/**
 * @file encoder.cpp
 * @brief 编码器
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-18
 */

#include "encoder.h"

class EncoderPrivate
{
public:
    EncoderPrivate()
    {
        m_polarity = Encoder::NORMAL;
        m_type = Encoder::QUAD;
        m_resolution = 48.0;
        m_origin = 0.0;
    }

    Encoder::Polarity m_polarity;
    Encoder::Type m_type;
    float m_resolution;
    float m_origin;
};

Encoder::Encoder(QObject *parent) :
    QObject(parent),
    d_ptr(new EncoderPrivate)
{

}

Encoder::~Encoder()
{
    delete d_ptr;
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

Encoder::Type Encoder::type() const
{
    Q_D(const Encoder);
    return d->m_type;
}

void Encoder::set_type(Encoder::Type type)
{
    Q_D(Encoder);
    d->m_type = type;
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
