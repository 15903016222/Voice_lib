#ifndef __DMA_H__
#define __DMA_H__

#include <QMutex>

namespace DplSource {

class DmaPrivate;

class Dma
{
public:
    static Dma *get_instance();
    static void destroyed();

    int get_region_size() const;

    unsigned int is_completed() const;
    void clean_completed();

    const char *get_data_buffer();

    const char *get_store_buffer();

    unsigned int get_data_dma_counter() const;
    void set_data_dma_counter(int value);

    unsigned int get_used_buffer_index() const;
    void set_used_buffer_index(int value);

    unsigned int get_scan_source() const;
    void set_scan_source(int value);

    unsigned int get_store_frame_count() const;
    void set_store_frame_count(int value);

    unsigned int get_encoder_counter_offset() const;
    void set_encoder_counter_offset(int value);

    unsigned int get_steps_per_resolution() const;
    void set_steps_per_resolution(int value);

    unsigned int get_scan_zero_index_offset() const;
    void set_scan_zero_index_offset(int value);

    unsigned int get_max_store_index() const;
    void set_max_store_index(int value);

    unsigned int get_scan_timmer_counter() const;
    void set_scan_timmer_counter(int value);

    unsigned int get_scan_timmer_circled() const;
    void set_scan_timmer_circled(int value);

    unsigned char get_scan_data_mark(int index) const;

protected:
    Dma();
    virtual ~Dma();

private:
    static QMutex m_mutex;
    static Dma *m_dma;

    DmaPrivate *d;
};

}

#endif // __DMA_H__
