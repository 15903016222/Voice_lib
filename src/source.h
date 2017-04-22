/**
 * @file source.h
 * @brief 数据源类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-18
 */

#ifndef __DPLSOURCE_SOURCE_H__
#define __DPLSOURCE_SOURCE_H__

#include "source_global.h"

#include <QObject>

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

//    void set_position(int scanAxis, int indexAxis);

public slots:
    /**
     * @brief restart   重新启动数据上传, 会延迟200ms后，启动数据上传
     */
    void restart();

signals:
    /**
     * @brief data_event    数据信号
     * @param data          数据
     */
    void data_event(const char *data);

    /**
     * @brief type_changed  源类型改变
     * @param type          源类型
     */
    void type_changed(Source::Type type);

protected:
    explicit Source();
    ~Source();

protected slots:
    void update();

private:
    SourcePrivate *d_ptr;
};

}

#endif // __DPLSOURCE_SOURCE_H__
