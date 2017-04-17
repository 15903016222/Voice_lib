#ifndef __DMA_H__
#define __DMA_H__

#include <QMutex>

namespace DplSource {

class DmaPrivate;

class Dma
{
public:
    static Dma *instance();

    /**
     * @brief region_size   缓冲区大小
     * @return              大小(Bytes)
     */
    int region_size() const;

    /**
     * @brief read_data 读取缓冲区数据
     * @return          数据地址
     */
    const char *read_data();

    /**
     * @brief get_store_buffer  最终数据保存的内存区域
     * @return                  内存地址
     */
    const char *get_store_buffer();

    unsigned int get_scan_source() const;
    void set_scan_source(int value);

    /**
     * @brief frame_size    获取一帧数据的大小
     * @return              数据大小(Bytes)
     */
    int frame_size() const;

    /**
     * @brief frame_count   获取DMA一次传输多少帧数据
     * @return              数量
     */
    int frame_count() const;

    /**
     * @brief set_frame_count   设置DMA传输多少帧数据
     * @param value             数量
     */
    void set_frame_count(int count);

    unsigned int get_encoder_counter_offset() const;
    void set_encoder_counter_offset(int value);

    unsigned int get_steps_per_resolution() const;
    void set_steps_per_resolution(int value);

    unsigned int get_scan_zero_index_offset() const;
    void set_scan_zero_index_offset(int value);

    unsigned int get_scan_timmer_counter() const;
    void set_scan_timmer_counter(int value);

    unsigned int get_scan_timmer_circled() const;
    void set_scan_timmer_circled(int value);

    unsigned char get_scan_data_mark(int index) const;

protected:
    Dma();
    virtual ~Dma();

private:
    DmaPrivate *d;
};

}

#endif // __DMA_H__
