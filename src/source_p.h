#ifndef __SOURCE_P_H__
#define __SOURCE_P_H__

#include "source.h"
#include "dma.h"

#include <QTimer>
#include <QReadWriteLock>

namespace DplSource {

class SourcePrivate
{
    Q_DECLARE_PUBLIC(Source)
public:
    SourcePrivate(Source *parent);

    void update_current_data();

    /* Attribution */
    mutable QReadWriteLock m_rwlock;

    QTimer m_timer;
    int m_interval;                 // 上传的间隔时间
    bool m_delayFlag;
    Source::Type m_type;

    Dma *m_dma;

private:
    Source * const q_ptr;
};

}
#endif // __SOURCE_P_H__
