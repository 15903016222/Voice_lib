/**
 * @file beam_group.h
 * @brief Beam组类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-18
 */

#ifndef __DPLSOURCE_BEAMS_H__
#define __DPLSOURCE_BEAMS_H__

#include "beam.h"

namespace DplSource {

class BeamsPrivate;
class SOURCESHARED_EXPORT Beams
{
public:
    explicit Beams(int beamQty, int pointQty, const char* data);

    ~Beams();

    /**
     * @brief get       获取指定Beam数据
     * @param index     Beam ID
     * @return          指向Beam数据的指针
     */
    BeamPointer get(int index) const;

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

    /**
     * @brief rf    获取是否为射频模式
     * @return      如果是射频，则返回true
     */
    bool rf() const;

    /**
     * @brief set_rf    设置射频
     * @param flag      true为射频
     */
    void set_rf(bool flag);

    /**
     * @brief raw_data  获取原始数据
     * @return          原始数据
     */
    const char *raw_data() const;

    /**
     * @brief set_raw_data  设置原始数据
     * @param data          原始数据
     */
    void set_raw_data(const char *data);

private:
    BeamsPrivate *d;
};

typedef QSharedPointer<Beams> BeamsPointer;

}

#endif // __DPLSOURCE_BEAMS_H__
