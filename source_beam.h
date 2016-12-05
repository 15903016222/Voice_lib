#ifndef __SOURCE_BEAM_H__
#define __SOURCE_BEAM_H__

#include <QObject>

namespace DplSource {

class SourceBeamPrivate;
class SourceBeam
{
public:
    SourceBeam(const int pointQty, const char *data = NULL);

    /**
     * @brief set_raw_data 设置Beam原始数据
     * @param data  指向Beam原始数据,调用要维护这个地址,不能删除
     */
    void set_raw_data(const char *data);

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
    SourceBeamPrivate *d;
};

}

#endif // __SOURCE_BEAM_H__
