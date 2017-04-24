/**
 * @file axis.h
 * @brief 轴类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-24
 */
#ifndef __DPLSOURCE_AXIS_H__
#define __DPLSOURCE_AXIS_H__

#include "source_global.h"
#include "encoder.h"

namespace DplSource {

class AxisPrivate;
class SOURCESHARED_EXPORT Axis : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Axis)
public:
    explicit Axis(QObject *parent = 0);
    ~Axis();

    /**
     * @brief driving 获取激励源
     * @return        激励源
     */
    const DrivingPointer &driving() const;

    /**
     * @brief set_driving   设置激励源
     * @param driving       激励源
     */
    void set_driving(const DrivingPointer &driving);

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
     * @brief resolution    获取扫查轴扫查分辨率
     * @return              分辨率(mm)
     */
    float resolution() const;

    /**
     * @brief set_resolution    设置分辨率
     * @param val               分辨率(mm)
     * @return                  设置成功返回true,否则false
     */
    bool set_resolution(float val);


signals:
    void start_changed(float start);
    void driving_changed(const DrivingPointer &driving);
    void resolution_changed(float val);

public slots:

private:
    AxisPrivate *d_ptr;
};

}

#endif // __DPLSOURCE_AXIS_H__
