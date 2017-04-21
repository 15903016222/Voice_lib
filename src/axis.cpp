#include "axis.h"

namespace DplSource {

class AxisPrivate
{
public:
    AxisPrivate() :
        m_drivingPtr(new Driving)
    {
        m_start = 0.0;
        m_end   = 800.0;
        m_resolution = 1.0;
    }
    DrivingPointer m_drivingPtr;
    float m_start;                  // 扫查起点(mm)
    float m_end;                    // 扫查终点(mm)
    float m_resolution;             // 扫查分辨率(mm)
};

Axis::Axis(QObject *parent) :
    QObject(parent),
    d_ptr(new AxisPrivate)
{

}

Axis::~Axis()
{
    delete d_ptr;
}

float Axis::start() const
{
    Q_D(const Axis);
    return d->m_start;
}

bool Axis::set_start(float val)
{
    Q_D(Axis);
    if (val < d->m_end) {
        d->m_start = val;
        return true;
    }
    return false;
}

float Axis::end() const
{
    Q_D(const Axis);
    return d->m_end;
}

bool Axis::set_end(float val)
{
    Q_D(Axis);
    if (val > d->m_start) {
        d->m_end = val;
        return true;
    }
    return false;
}

float Axis::resolution() const
{
    Q_D(const Axis);
    return d->m_resolution;
}

bool Axis::set_resolution(float val)
{
    Q_D(Axis);
    d->m_resolution = val;
    emit resolution_changed(val);
}
}
