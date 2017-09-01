/**
 * @file scan.cpp
 * @brief 扫查配置类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-24
 */

#include "scan_p.h"

namespace DplSource {

Scan::Scan(QObject *parent) :
    QObject(parent),
    d_ptr(new ScanPrivate(this))
{
}

Scan::~Scan()
{
    delete d_ptr;
}

Scan *Scan::instance()
{
    static Scan *ins = new Scan();
    return ins;
}

Scan::Mode Scan::mode() const
{
    Q_D(const Scan);
    return d->mode();
}

void Scan::set_mode(Scan::Mode mode)
{
    Q_D(Scan);
    d->set_mode(mode);
}

const AxisPointer &Scan::scan_axis() const
{
    Q_D(const Scan);
    return d->m_scanAxis;
}

const AxisPointer &Scan::index_axis() const
{
    Q_D(const Scan);
    return d->m_indexAxis;
}

const EncoderPointer &Scan::encoder_x() const
{
    Q_D(const Scan);
    return d->m_encX;
}

const EncoderPointer &Scan::encoder_y() const
{
    Q_D(const Scan);
    return d->m_encY;
}

double Scan::speed() const
{
    Q_D(const Scan);
    return d->m_speed;
}

void Scan::set_speed(double val)
{
    Q_D(Scan);
    d->m_speed = val;
}

}
