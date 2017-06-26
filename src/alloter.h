/**
 * @file alloter.h
 * @brief 分配器，分配各Beams的数据资源
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2017-02-10
 */
#ifndef __DPLSOURCE_ALLOTER_H__
#define __DPLSOURCE_ALLOTER_H__

#include <QReadWriteLock>

#include "beams.h"

#include "scan.h"

namespace DplSource {

class Alloter : public QObject
{
    Q_OBJECT
public:
    static Alloter *instance();

    /**
     * @brief add   向分配器注册一个Beams对象
     * @param beams Beams对象指针
     */
    void add(Beams *beams);

    /**
     * @brief remove    注销一个Beams对象
     * @param beams     Beams对象指针
     */
    void remove(Beams *beams);

protected:
    explicit Alloter(QObject *parent = 0);

private slots:
    void do_data_event(const char *data);
    void set_dma_driving_type(const DrivingPointer &drivingPtr);
    void set_dma_frame_count();
    void set_dma_encoder_offset(int qty);
    void set_dma_steps_resolution();
    void set_dma_start_offset();

private:
    QList<Beams *> m_beamsList;
    QReadWriteLock m_rwlock;
};

}

#endif // __DPLSOURCE_ALLOTER_H__
