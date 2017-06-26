/**
 * @file beam_group.h
 * @brief Beam组类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-18
 */

#ifndef __DPLSOURCE_BEAMS_H__
#define __DPLSOURCE_BEAMS_H__

#include <QObject>
#include <QSharedPointer>
#include "beam.h"

#include "source_global.h"

namespace DplSource {

class BeamsPrivate;
class SOURCESHARED_EXPORT Beams : public QObject
{
    Q_OBJECT
public:
    explicit Beams(QObject *parent = 0);
    ~Beams();

    /**
     * @brief get       获取指定Beam数据
     * @param index     Beam ID
     * @return          指向Beam数据的指针
     */
    const BeamPointer get(int index);


    /**
     * @brief beam_qty  获取Beam数量
     * @return          数量值
     */
    int beam_qty() const;

    /**
     * @brief point_qty 获取一条Beam的点数量
     * @return          点数量值
     */
    int point_qty() const;

    /**
     * @brief size  获取数据大小
     * @return      大小(Bytes)
     */
    int size() const;

protected:
    friend class Alloter;
    /**
     * @brief set_raw_data  设置原始数据
     * @param data          原始数据
     */
    void set_raw_data(const char *data);

public slots:
    /**
     * @brief set_beam_qty  设置Beam数量
     * @param qty           数量值
     */
    void set_beam_qty(int qty);

    /**
     * @brief set_point_qty 设置一条Beam的点数量
     * @param qty           点数量值
     */
    void set_point_qty(int qty);

signals:
    void data_event();
    void beam_qty_changed(int qty);
    void point_qty_changed(int qty);

private:
    BeamsPrivate *d;
};

typedef QSharedPointer<Beams> BeamsPointer;

}

#endif // __DPLSOURCE_BEAMS_H__
