#ifndef __SOURCE_H__
#define __SOURCE_H__

#include "group.h"

#include <QMutex>
#include <QObject>
#include <QSharedPointer>

namespace DplSource {

typedef QSharedPointer<Group> GroupSourcePointer;
class SourcePrivate;

class SOURCESHARED_EXPORT Source : public QObject
{
    Q_OBJECT
public:
    static Source *get_instance();
    static void destroyed();

    enum Type {
        SOURCE_DMA,
        SOURCE_FILE,
        SOURCE_NET
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
     * @brief set_interval  设置上传数据间隔时间
     * @param interval      间隔时间值
     */
    void set_interval(unsigned int interval);

    /**
     * @brief set_freeze    设置冻结，停止数据上传
     */
    void freeze();

    /**
     * @brief is_freeze 判断是冻结
     * @return          已冻结返回true，否则返回false
     */
    bool is_freeze();

    /**
     * @brief start 开始工作，数据上传
     */
    void start();

    static const int MAX_GROUPS;
    int groups();
    bool create_group(int beamNum, int pointNum);
    bool remove_group();
    const GroupSourcePointer &get_group(int index);

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
