#ifndef __SOURCE_H__
#define __SOURCE_H__

#include "group_source.h"

#include <QMutex>
#include <QObject>
#include <QSharedPointer>

namespace DplSource {

typedef QSharedPointer<GroupSource> GroupSourcePointer;
class SourcePrivate;

class SOURCESHARED_EXPORT Source : public QObject
{
    Q_OBJECT
public:
    enum Type {
        SOURCE_DMA,
        SOURCE_FILE,
        SOURCE_NET
    };

    void set_type(Type type);

    /**
     * @brief set_interval  设置上传数据间隔时间
     * @param interval      间隔时间值
     */
    void set_interval(unsigned int interval);

    void set_freeze(bool flag);
    bool is_freeze();

    static Source *get_instance();
    static void destroyed();

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
