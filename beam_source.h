#ifndef __BEAM_SOURCE_H__
#define __BEAM_SOURCE_H__

#include "source_global.h"
#include <QObject>

namespace DplSource {

class BeamSourcePrivate;
class SOURCESHARED_EXPORT BeamSource
{
public:
    BeamSource(const char *data = NULL, int size = 0);

    /**
     * @brief set_raw_data 设置Beam原始数据
     * @param data  指向Beam原始数据,调用要维护这个地址,不能删除
     */
    void set_raw_data(const char *data, int size);

    bool get_wave(QByteArray &wave);
    int point_qty();
    int index();
    int gate_a_height();
    int gate_a_position();
    int gate_b_height();
    int gate_b_position();
    int gate_i_height();
    int gate_i_position();
    int encoder_x();
    int encoder_y();

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
