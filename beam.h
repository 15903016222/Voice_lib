#ifndef __BEAM_SOURCE_H__
#define __BEAM_SOURCE_H__

#include "source_global.h"
#include <QObject>

namespace DplSource {

class BeamSourcePrivate;
class SOURCESHARED_EXPORT Beam
{
public:
    Beam();
    ~Beam();

    /**
     * @brief set_raw_data 设置Beam原始数据
     * @param data  指向Beam原始数据,调用要维护这个地址,不能删除
     * @param pointNum 波形点数
     */
    void set_raw_data(const char *data, int pointNum);
    bool has_data();
    void clean();

    bool get_wave(QByteArray &wave);
    int point_qty() const;
    int index() const;
    int gate_a_height() const;
    int gate_a_position() const;
    int gate_b_height() const;
    int gate_b_position() const;
    int gate_i_height() const;
    int gate_i_position() const;
    int encoder_x() const;
    int encoder_y() const;

//    bool led0();
//    bool led1();
//    bool led2();
//    bool buzzer();
//    int analog_output0();
//    int analog_output1();

private:
    BeamSourcePrivate *d;
};

}

#endif // __BEAM_SOURCE_H__
