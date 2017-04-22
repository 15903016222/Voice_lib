/**
 * @file alloter.h
 * @brief 分配器，分配各BeamGroup的数据资源
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2017-02-10
 */
#ifndef __DPLSOURCE_ALLOTER_H__
#define __DPLSOURCE_ALLOTER_H__

#include <QReadWriteLock>

#include "beam_group.h"

#include "scan.h"

namespace DplSource {

class Alloter : public QObject
{
    Q_OBJECT
public:
    static Alloter *instance();

    /**
     * @brief add   向分配器注册一个BeamGroup对象
     * @param beams BeamGroup对象指针
     */
    void add(BeamGroup *beams);

    /**
     * @brief remove    注销一个BeamGroup对象
     * @param beams     BeamGroup对象指针
     */
    void remove(BeamGroup *beams);

public slots:
    void do_data_event(const char *data);
    void do_scan_axis_driving_changed(const DrivingPointer &drivingPtr);
    void do_beam_group_changed();
    void do_point_qty_changed(int qty);
    void set_dma_steps_resolution();
    void set_dma_start_offset();

protected:
    explicit Alloter(QObject *parent = 0);

private:
    QList<BeamGroup *> m_beamGroups;
    QReadWriteLock m_rwlock;
};

}

#endif // __DPLSOURCE_ALLOTER_H__
