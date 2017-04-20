#ifndef __DPLSOURCE_SCAN_H__
#define __DPLSOURCE_SCAN_H__

#include "encoder.h"

namespace DplSource {

class ScanPrivate;
class SOURCESHARED_EXPORT Scan : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Scan)
public:
    explicit Scan();
    ~Scan();

    enum Mode {
        ONELINE,
        RASTER,
    };

    /**
     * @brief scan_axis_driving 获取激励源
     * @return                  激励源
     */
    const DrivingPointer &scan_axis_driving() const;

    /**
     * @brief set_scan_axis_driving 设置激励源
     * @param driving               激励源
     */
    void set_scan_axis_driving(const DrivingPointer &driving);

    /**
     * @brief speed 获取扫查速度
     * @return      扫查速度(mm/s)
     */
    float speed() const;

    /**
     * @brief set_speed 设置扫查速度
     * @param val       扫查速度(mm/s)
     */
    void set_speed(float val);

    /**
     * @brief start 获取扫查起点
     * @return      位置(mm)
     */
    float start() const;

    /**
     * @brief set_start 设置扫查起点
     * @param val       位置(mm)
     * @return          设置成功返回true，否则false
     */
    bool set_start(float val);

    /**
     * @brief end   获取扫查终点
     * @return      位置(mm)
     */
    float end() const;

    /**
     * @brief set_end   设置扫查终点
     * @param val       位置(mm)
     * @return          设置成功返回true,否则false
     */
    bool set_end(float val);

    /**
     * @brief resolution    获取分辨率
     * @return              分辨率(mm)
     */
    float resolution() const;

    /**
     * @brief set_resolution    设置分辨率
     * @param val               分辨率(mm)
     * @return                  设置成功返回true,否则false
     */
    bool set_resolution(float val);

    enum ResetMode {
        ENCODER = 0x01,
        DATA    = 0x02,
        ALL = ENCODER | DATA
    };
    ResetMode reset_mode() const;

    void set_reset_mode(ResetMode mode);

    void reset();

    void pause();

    bool is_pause();

signals:
    void driving_changed(const DrivingPointer &driving);

private:
    ScanPrivate *d_ptr;
};

typedef QSharedPointer<Scan> ScanPointer;

}

#endif // __DPLSOURCE_SCAN_H__
