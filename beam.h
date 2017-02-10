#ifndef __BEAM_SOURCE_H__
#define __BEAM_SOURCE_H__

#include "source_global.h"
#include <QObject>
#include <QSharedPointer>

namespace DplSource {

class Beam;
class BeamSourcePrivate;

typedef QSharedPointer<Beam> BeamPointer;

class SOURCESHARED_EXPORT Beam
{
public:
    Beam();
    ~Beam();

    /**
     * @brief set_raw_data  设置Beam原始数据
     * @param data          指向Beam原始数据,调用者要维护这个地址,不能删除
     * @param pointNum      波形点数
     */
    void set_raw_data(const char *data, int pointNum);

    /**
     * @brief has_data  判断是否有数据
     * @return          有数据则返回true，否则返回false
     */
    bool has_data() const;

    /**
     * @brief clean 清除数据
     */
    void clean();

    /**
     * @brief get_wave  获取波形数据
     * @param wave      波形数据
     * @return          成功返回true，失败返回false
     */
    bool get_wave(QByteArray &wave) const;

    /**
     * @brief point_qty 获取波形点数
     * @return          点数
     */
    int point_qty() const;

    /**
     * @brief index 获取Beam序号
     * @return      序号
     */
    int index() const;

    /**
     * @brief gate_a_height 获取闸门A内波形峰值
     * @return              峰值
     */
    int gate_a_height() const;

    /**
     * @brief gate_a_position   获取闸门A内波形峰值对应的位置
     * @return                  位置(ns)
     */
    int gate_a_position() const;

    /**
     * @brief gate_b_height 获取闸门B内波形峰值
     * @return              峰值
     */
    int gate_b_height() const;

    /**
     * @brief gate_B_position   获取闸门B内波形峰值对应的位置
     * @return                  位置(ns)
     */
    int gate_b_position() const;

    /**
     * @brief gate_i_height 获取闸门I内波形峰值
     * @return              峰值
     */
    int gate_i_height() const;

    /**
     * @brief gate_i_position   获取闸门i内波形峰值对应的位置
     * @return                  位置
     */
    int gate_i_position() const;

    /**
     * @brief encoder_x 获取编码器X值
     * @return          编码器X数据
     */
    int encoder_x() const;

    /**
     * @brief encoder_y 获取编码器Y值
     * @return          编码器Y数据
     */
    int encoder_y() const;

//    bool led0();
//    bool led1();
//    bool led2();
//    bool buzzer();
//    int analog_output0();
//    int analog_output1();

    static const int MEASURE_SIZE;
private:
    BeamSourcePrivate *d;
};

}

#endif // __BEAM_SOURCE_H__
