/**
 * @file encoder.h
 * @brief 编码器
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-18
 */

#ifndef __DPLSOURCE_ENCODER_H__
#define __DPLSOURCE_ENCODER_H__

#include "source_global.h"

#include <QObject>
#include <QSharedPointer>

namespace DplSource {

class EncoderPrivate;
class SOURCESHARED_EXPORT Encoder : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Encoder)
public:
    explicit Encoder(int id = 1, QObject *parent = 0);
    ~Encoder();

    /**
     * @brief index 获取编码器序号(1,2)
     * @return      序号
     */
    int index() const;

    /**
     * @brief set_index 设置编码器序号(1,2)
     * @param i         序号
     */
    void set_index(int i);

    enum Polarity {
        NORMAL,     // 正常
        INVERSE     // 反向
    };

    /**
     * @brief polarity  获取极性
     * @return          极性
     */
    Polarity polarity() const;

    /**
     * @brief set_polarity  设置极性
     * @param val           极性
     */
    void set_polarity(Polarity val);

    enum Mode {
        OFF     = 0b000,
        DOWN    = 0b001,
        UP      = 0b010,
        QUAD    = 0b011
    };

    /**
     * @brief mode  获取类型
     * @return      类型
     */
    Mode mode() const;

    /**
     * @brief set_mode  设置类型
     * @param mode      类型
     */
    void set_mode(Mode mode);

    /**
     * @brief resolution    编码器每个毫米包含的计数
     * @return              数值(步/毫米，step/mm)
     */
    float resolution() const;

    /**
     * @brief set_resolution    设置每个毫米包含的计数
     * @param val               数值(步/毫米，step/mm)
     */
    void set_resolution(float val);

    /**
     * @brief origin    获取起点
     * @return          起点值(mm)
     */
    float origin() const;

    /**
     * @brief set_origin    设置起点
     * @param val           起点值(mm)
     */
    void set_origin(float val);

signals:
    void mode_changed(DplSource::Encoder::Mode mode);
    void resolution_changed(float val);

private:
    EncoderPrivate *d_ptr;
};

typedef QSharedPointer<Encoder> EncoderPointer;

}

#endif // __DPLSOURCE_ENCODER_H__
