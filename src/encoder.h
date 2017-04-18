/**
 * @file encoder.h
 * @brief 编码器
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-18
 */

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "source_global.h"
#include <QSharedPointer>

class EncoderPrivate;
class Encoder : public QObject
{
    Q_DECLARE_PRIVATE(Encoder)
    Q_OBJECT
public:
    explicit Encoder(QObject *parent = 0);
    ~Encoder();

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

    enum Type {
        QUAD,
        UP,
        DOWN
    };

    /**
     * @brief type  获取类型
     * @return      类型
     */
    Type type() const;

    /**
     * @brief set_type  设置类型
     * @param type      类型
     */
    void set_type(Type type);

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

public slots:

private:
    EncoderPrivate *d_ptr;
};

typedef QSharedPointer<Encoder> EncoderPointer;

#endif // __ENCODER_H__
