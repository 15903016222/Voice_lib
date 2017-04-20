#include "scan.h"

namespace DplSource {

class ScanPrivate
{
public:
    ScanPrivate() :
        m_drivingPtr(new Driving)
    {
        m_speed = 20.0;
        m_start = 0.0;
        m_end   = 800.0;
        m_resolution = 1.0;
    }

    DrivingPointer m_drivingPtr;
    float m_speed;                  // 扫查速度(mm/s)
    float m_start;                  // 扫查起点(mm)
    float m_end;                    // 扫查终点(mm)
    float m_resolution;             // 扫查分辨率(mm)
};

Scan::Scan() :
    d_ptr(new ScanPrivate)
{

}

Scan::~Scan()
{
    delete d_ptr;
}

const DrivingPointer &Scan::scan_axis_driving() const
{
    Q_D(const Scan);
    return d->m_drivingPtr;
}

void Scan::set_scan_axis_driving(const DrivingPointer &driving)
{
    Q_D(const Scan);
    if (driving && driving != d->m_drivingPtr) {
        d->m_drivingPtr = driving;
        emit driving_changed(driving);
    }
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

float Scan::start() const
{
    Q_D(const Scan);
    return d->m_start;
}

bool Scan::set_start(float val)
{
    Q_D(Scan);
    if (val < d->m_end) {
        d->m_start = val;
        return true;
    }
    return false;
}

float Scan::end() const
{
    Q_D(const Scan);
    return d->m_end;
}

bool Scan::set_end(float val)
{
    Q_D(Scan);
    if (val > d->m_start) {
        d->m_end = val;
        return true;
    }
    return false;
}

float Scan::resolution() const
{
    Q_D(const Scan);
    return d->m_resolution;
}

bool Scan::set_resolution(float val)
{
    Q_D(Scan);
    d->m_resolution = val;
}

}
