#ifndef __SOURCE_P_H__
#define __SOURCE_P_H__

#include "source.h"
#include "scan.h"
#include "dma.h"

#include <QThread>
#include <QReadWriteLock>

namespace DplSource {

static const int MAX_GROUP = 8;
struct GroupInfo
{
    GroupInfo(int beamQty = 0, int pointQty = 0) :
        beamQty(beamQty),
        pointQty(pointQty),
        offset(0),
        valid(false)
    {}

    int beamQty;
    int pointQty;
    int offset;     // 数据在当前帧的偏移位置
    bool valid;     // 标志该组是否启用
};

class SourcePrivate : public QThread
{
    Q_OBJECT
public:
    SourcePrivate(Source *source);

    void update_offset();

public slots:
    void do_scanAxis_driving_changed(DplSource::Axis::Driving driving);
    void update_dma_encoder_offset(int qty);
    void do_encoderX_resolution();
    void do_scanAxis_changed();

protected:
    void run();

private:
    Source *q_ptr;

public:
    /* Attribution */
    mutable QReadWriteLock m_rwlock;

    int m_interval;                 // 上传的间隔时间(ms)
    Source::Type m_type;

    Dma *m_dma;

    GroupInfo m_groups[MAX_GROUP];
    int m_beamsSize;                 // 数据大小(Bytes)
    int m_frameSize;                // 帧大小(Bytes)
    const char *m_curData;          // 指向当前数据
    const char *m_data;             // 指向全部数据

};

}
#endif // __SOURCE_P_H__
