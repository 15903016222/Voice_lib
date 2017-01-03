#ifndef __GROUP_SOURCE_H__
#define __GROUP_SOURCE_H__

#include "beam.h"

namespace DplSource {

class SOURCESHARED_EXPORT GroupPrivate;

class Group
{
public:
    Group(int beamNum, int pointNum);
    ~Group();

    /**
     * @brief set_raw_data  设置原始数据
     * @param rawData       指向原始数据
     */
    void set_raw_data(const char *rawData);

    /**
     * @brief set_beam_qty  设置组的Beam数量
     * @param qty           数量
     */
    void set_beam_qty(int qty);

    /**
     * @brief beam_qty  获取组的Beam数量
     * @return          Beam数
     */
    int beam_qty();

    /**
     * @brief set_point_qty 设置一条Beam包含的点数
     * @param qty           点数
     */
    void set_point_qty(int qty);

    /**
     * @brief point_qty 获取一条Beam包含的点数
     * @return          点数
     */
    int point_qty();

    /**
     * @brief size  获取组数据的大小
     * @return      数据大小， 单位(Byte)
     */
    int size();

    /**
     * @brief get_beam  获取指定Beam的数据
     * @param beamNo    Beam号
     * @param beam      保存Beam数据
     * @return          成功返回true，失败返回false
     */
    bool get_beam(int beamNo, Beam &beam) const;

private:
    GroupPrivate *d;
};

}

#endif // __GROUP_SOURCE_H__
