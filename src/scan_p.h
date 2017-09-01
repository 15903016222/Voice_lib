#ifndef __DPLSOURCE_SCAN_P_H__
#define __DPLSOURCE_SCAN_P_H__

#include "scan.h"

namespace DplSource {

class ScanPrivate : public QObject
{
    Q_OBJECT
public:
    ScanPrivate(Scan *parent);

    double m_speed;             // 扫查速度(mm/s)
    EncoderPointer m_encX;      // 编码器X
    EncoderPointer m_encY;      // 编码器Y
    AxisPointer m_scanAxis;     // 扫查轴
    AxisPointer m_indexAxis;    // 步进轴

    Scan::Mode mode() const;
    void set_mode(Scan::Mode mode);

protected slots:
    void do_scanAxis_driving_changed(DplSource::Axis::Driving driving);
    void do_indexAxis_driving_changed(DplSource::Axis::Driving driving);

private:
    Scan::Mode m_mode;          // 扫查模式
    Scan *q_ptr;
};

inline Scan::Mode ScanPrivate::mode() const
{
    return m_mode;
}

}

#endif // __DPLSOURCE_SCAN_P_H__
