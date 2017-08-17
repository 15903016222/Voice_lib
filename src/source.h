/**
 * @file source.h
 * @brief 数据源类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-18
 */

#ifndef __DPLSOURCE_SOURCE_H__
#define __DPLSOURCE_SOURCE_H__

#include "beams.h"

namespace DplSource {

class SourcePrivate;
class SOURCESHARED_EXPORT Source : public QObject
{
    Q_DECLARE_PRIVATE(Source)
    Q_OBJECT
public:
    /**
     * @brief instance  获取单例对象
     * @return          单例对象指针
     */
    static Source *instance();

    /**
     * @brief register_group    向数据源注册一组数据
     * @param grp               组号,从0开始
     * @param beamQty           聚焦数
     * @param pointQty          采样点数
     * @return                  注册成功返回true，否则返回false
     */
    bool register_group(int grp, int beamQty, int pointQty);

    /**
     * @brief unregister_group  向数据源注销一组数据
     *@param grp               组号,从0开始
     *@return                  成功返回true，否则返回false
     */
    bool unregister_group(int grp);

    /**
     *@brief edit_group    修改注册组信息
     *@param grp           组号
     *@param beamQty       聚焦数
     *@param pointQty      采样点数
     *@return              成功返回true，失败返回false
     */
    bool edit_group(int grp, int beamQty, int pointQty);

    /**
     *@brief current_beams 获取当前指定组数据Beams
     *@param grp           组号
     *@return              返回Beams
     */
    BeamsPointer current_beams(int grp) const;

    /**
     *@brief beams         获取指定帧号的组数据
     *@param grp           组号，从0开始
     *@param frameIndex    帧号，从0开始
     *@return              返回Beams
     */
    BeamsPointer beams(int grp, int frameIndex) const;

    /**
     *@brief beams 获取指定编码器位置的组数据
     *@param grp   组号
     *@param x     x坐标(mm)
     *@param y     y坐标(mm)
     *@return      返回Bemas
     */
    BeamsPointer beams(int grp, int x, int y) const;

    enum Type {
        DMA,     /* DMA源 */
        FILE,    /* 文件源 */
        NET      /* 网络源 */
    };

    /**
     * @brief type  获取数据源类型
     * @return      类型
     */
    Type type() const;

    /**
     * @brief set_type  设置数据源类型
     * @param type      类型
     */
    void set_type(Type type);

    /**
     * @brief interval  获取上传数据时间间隔
     * @return          时间间隔，单位(ms)
     */
    int interval() const;

    /**
     * @brief set_interval  设置上传数据时间间隔
     * @param interval      时间间隔, 单位(ms)
     */
    void set_interval(unsigned int interval);

    /**
     * @brief stop  停止数据上传
     */
    void stop();

    /**
     * @brief is_running    判断是否在运行
     * @return              在运行则返回true，否则为false
     */
    bool is_running() const;

    /**
     * @brief start 启动数据上传
     */
    void start();

public slots:
    /**
     * @brief restart   重新启动数据上传, 会延迟200ms后，启动数据上传
     */
    void restart();

signals:
    /**
     * @brief data_event    数据信号
     */
    void data_event();

    /**
     * @brief type_changed  源类型改变
     * @param type          源类型
     */
    void type_changed(Source::Type type);

protected:
    explicit Source();
    ~Source();

private:
    SourcePrivate *d_ptr;
};

}

#endif // __DPLSOURCE_SOURCE_H__
