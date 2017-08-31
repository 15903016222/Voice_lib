/**
 * @file scan.cpp
 * @brief 扫查配置类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-24
 */

#include "scan.h"

namespace DplSource {

class ScanPrivate
{
public:
    ScanPrivate() :
        m_speed(20.0),
        m_mode(Scan::ONELINE),
        m_scanAxis(new Axis),
        m_indexAxis(new Axis)
    {
        m_indexAxis->encoder()->set_type(Encoder::Y);
    }

    double m_speed;     // 扫查速度(mm/s)
    Scan::Mode m_mode;  // 扫查模式
    AxisPointer m_scanAxis;   // 扫查轴
    AxisPointer m_indexAxis;  // 步进轴
};

Scan::Scan(QObject *parent) :
    QObject(parent),
    d_ptr(new ScanPrivate)
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
    return d->m_mode;
}

void Scan::set_mode(Scan::Mode mode)
{
    Q_D(Scan);
    if (mode != d->m_mode) {
        d->m_mode = mode;
        emit mode_changed(mode);
    }
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
