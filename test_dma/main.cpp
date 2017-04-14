#include <QCoreApplication>
#include "dma.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    DplSource::Dma *dma = DplSource::Dma::instance();

    qDebug("%s[%d]:\n"
           "data dma count = %d\n"
           "buffer index = %d\n"
           "scan source = %d\n"
           "frame count = %d\n"
           "encoder counter offset = %d\n"
           "steps per resolution = %d\n"
           "scan zero index offset = %d\n"
           "max store index = %d\n"
           "scan timer counter = %d\n"
           "scan timer circled = %d\n",
           __func__,__LINE__,
           dma->get_data_dma_counter(),
           dma->get_used_buffer_index(),
           dma->get_scan_source(),
           dma->get_store_frame_count(),
           dma->get_encoder_counter_offset(),
           dma->get_steps_per_resolution(),
           dma->get_scan_zero_index_offset(),
           dma->get_max_store_index(),
           dma->get_scan_timmer_counter(),
           dma->get_scan_timmer_circled());

    return 0;
}
