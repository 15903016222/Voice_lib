/**
 * @file beam.h
 * @brief beam类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-18
 */

#ifndef __DPLSOURCE_BEAM_H__
#define __DPLSOURCE_BEAM_H__

#include "source_global.h"

#include <QObject>
#include <QSharedPointer>

namespace DplSource {

class BeamPrivate;
class SOURCESHARED_EXPORT Beam
{
public:
    static const int MEASURE_SIZE = 32;
    static const float MAX_GATE_HEIGHT;

    explicit Beam();
    ~Beam();

    /**
     * @brief clean 清除数据
     */
    void clean();

    /**
     * @brief wave      获取波形数据
     * @return          波形数据
     */
    const QByteArray &wave() const;

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
     * @brief encoder_x 获取编码器X值
     * @return          编码器X数据
     */
    int encoder_x() const;

    /**
     * @brief encoder_y 获取编码器Y值
     * @return          编码器Y数据
     */
    int encoder_y() const;

    /**
     * @brief The GateType enum 闸门类型
     */
    enum GateType {
        GATE_A,
        GATE_B,
        GATE_I
    };

    /**
     * @brief gate_a_peak
     *
     * @return
     */
    /**
     * @brief gate_peak     获取指定闸门内测得信号的峰值波幅
     * @param gate          闸门类型
     * @return              波幅(%)
     */
    float gate_peak(GateType gate) const;

    /**
     * @brief gate_minus    计算指定闸门内的峰值与闸门阈值幅度之差
     * @param gate          闸门类型
     * @param height        闸门阈值幅度
     * @return              差值(dB)
     */
    float gate_minus(GateType gate, int height);

    /**
     * @brief gate_peak_position    获取指定闸门内测得信号的峰值位置
     * @param gate                  闸门类型
     * @return                      位置(采样精度)
     */
    int gate_peak_position(GateType gate);

//    bool led0();
//    bool led1();
//    bool led2();
//    bool buzzer();
//    int analog_output0();
//    int analog_output1();

protected:
    friend class Beams;
    /**
     * @brief set_raw_data  设置Beam原始数据
     * @param data          指向Beam原始数据,调用者要维护这个地址,不能删除
     * @param rf            射频标志
     * @param pointNum      波形点数
     */
    void set_raw_data(const char *data, int pointNum, bool rf = false);

private:
    BeamPrivate *d;
};

typedef QSharedPointer<Beam> BeamPointer;

}

#endif // __DPLSOURCE_BEAM_H__
