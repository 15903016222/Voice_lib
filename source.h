#ifndef __SOURCE_H__
#define __SOURCE_H__

#include "group.h"

#include <QMutex>
#include <QObject>
#include <QSharedPointer>

namespace DplSource {

typedef QSharedPointer<Group> GroupPointer;
class SourcePrivate;

class SOURCESHARED_EXPORT Source : public QObject
{
    Q_OBJECT
public:
    static Source *get_instance();
    static void destroyed();

    enum Type {
        SOURCE_DMA,     /* DMA源 */
        SOURCE_FILE,    /* 文件源 */
        SOURCE_NET      /* 网络源 */
    };

    /**
     * @brief type  获取数据源类型
     * @return      类型
     */
    Type type();

    /**
     * @brief set_type  设置数据源类型
     * @param type      类型
     */
    void set_type(Type type);

    /**
     * @brief interval  获取上传数据时间间隔
     * @return          时间间隔，单位(ms)
     */
    int interval();

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
    bool is_running();

    /**
     * @brief start 启动数据上传
     * @param delay 延迟启动时间，单位(ms)
     *              如果为0，则立即启动；否则延迟delay时间后启动
     */
    void start(int delay=0);

    static const int MAX_GROUPS;
    int groups();
    bool add_group(int beamQty, int pointQty);
    bool remove_group(int index);
    const GroupPointer &get_group(int index);

//    void set_position(int scanAxis, int indexAxis);

signals:
    void data_event();

protected:
    explicit Source();
    virtual ~Source();

protected slots:
    void update();

private:
    static QMutex m_mutex;
    static Source *m_source;
    SourcePrivate *d;
};

}

#endif // __SOURCE_H__
