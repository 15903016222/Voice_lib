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
    ScanPrivate()
    {
        m_speed = 20.0;
        m_scanAxis = new Axis;
        m_indexAxis = new Axis;
    }

    float m_speed;      // 扫查速度(mm/s)
    Axis *m_scanAxis;     // 扫查轴
    Axis *m_indexAxis;    // 步进轴
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

Axis *Scan::scan_axis() const
{
    Q_D(const Scan);
    return d->m_scanAxis;
}

Axis *Scan::index_axis() const
{
    Q_D(const Scan);
    return d->m_indexAxis;
}

float Scan::speed() const
{
    Q_D(const Scan);
    return d->m_speed;
}

void Scan::set_speed(float val)
{
    Q_D(Scan);
    d->m_speed = val;
}

}
