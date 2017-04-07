#include "dma.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#include <QFile>
#include <QReadWriteLock>

namespace DplSource {

QMutex Dma::m_mutex;
Dma *Dma::m_dma = NULL;

static const char *MEM_DEVICE              = "/dev/mem";
static const quint32 DATA_BUFFER_ADDR      = 0x8f000000;
static const quint32 STORE_BUFFER_ADDR     = 0x90000000;
static const int CONFIG_OFFSET             = 0x00100000;
static const int SCAN_DATA_MARK_OFFSET     = 0x00200000;
static const int REGION_SIZE               = 0x00040000;
static const int DMA_DATA_OFFSET           = 2;

struct DmaParameter
{
    int completeFlag;           /*DMA完成传输标志,驱动程序置位*/
    int counter;                /*DMA传输次数*/
    int usedBufferIndex;        /*标志使用哪个缓冲区0～3*/
    int scanSource;             /*扫查源: 0,定时器； 1,一维编码器； 2，二维编码器*/
    int frameCount;             /*DMA一次传输多少帧数据，一帧数据大小为1K（驱动设置为1K）*/
    int encoderOffset;          /*编码器在Beam中的偏移位置（Phascan只有X编码器）*/
    int stepResolution;         /*编码器分辩率*/
    int scanZeroIndexOffset;    /*编码器起点*/
    int maxStoreIndex;          /*最大保存数*/
    int scanTimmerCounter;      /*保存到storebuffer的次数*/
    int scanTimmerCircled;      /*定时器搜查源，保存循环次数（保存完整个storebuffer后，从头开始保存）*/
};


class DmaPrivate
{
public:
    DmaPrivate();
    ~DmaPrivate();

public:
    int m_fd;
    volatile DmaParameter *m_param;
    char *m_dataBuffer;
    char *m_storeBuffer;
    volatile quint8 *m_scanDataMark;

    QReadWriteLock m_rwlock;
};

DmaPrivate::DmaPrivate()
{
    if ((m_fd = ::open(MEM_DEVICE, O_RDWR | O_SYNC)) == -1) {
        qFatal("open memory device failed");
    }

    m_dataBuffer = (char *)::mmap (0,  16 * 1024 * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd, DATA_BUFFER_ADDR);
    if (MAP_FAILED == m_dataBuffer) {
        qFatal("Mmap 0x%08x failed", DATA_BUFFER_ADDR);
    }

    m_storeBuffer = (char *)::mmap (0, 256 * 1024 * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd, STORE_BUFFER_ADDR);
    if (MAP_FAILED == m_storeBuffer) {
        qFatal("Mmap 0x%08x failed", STORE_BUFFER_ADDR);
    }


    m_param = (struct DmaParameter *)(m_dataBuffer + CONFIG_OFFSET);
    m_scanDataMark = (unsigned char *)(m_dataBuffer + SCAN_DATA_MARK_OFFSET);
}

DmaPrivate::~DmaPrivate()
{
    ::munmap((void *)m_dataBuffer,  16 * 1024 * 1024);
    ::munmap((void *)m_storeBuffer, 256 * 1024 * 1024);
    ::close(m_fd);
}


/*** DMA ***/
int Dma::get_region_size() const
{
    return REGION_SIZE;
}

unsigned int Dma::is_completed() const
{
    QReadLocker l(&d->m_rwlock);
    return d->m_param->completeFlag;
}

void Dma::clean_completed()
{
    QWriteLocker l(&d->m_rwlock);
    d->m_param->completeFlag = 0;
}

const char *Dma::get_data_buffer()
{
    QReadLocker l(&d->m_rwlock);

    int i = (d->m_param->counter + 3) & 0x3;
    if (i == d->m_param->usedBufferIndex) {
        i = (i+3) & 0x3;
    }

    d->m_param->usedBufferIndex = i;

    return d->m_dataBuffer + DMA_DATA_OFFSET + REGION_SIZE * i;
}

const char *Dma::get_store_buffer()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_storeBuffer;
}

unsigned int Dma::get_data_dma_counter() const
{
	QReadLocker l(&d->m_rwlock);
    return d->m_param->counter;
}

void Dma::set_data_dma_counter(int value)
{
	QWriteLocker l(&d->m_rwlock);
    d->m_param->counter = value;
}

unsigned int Dma::get_used_buffer_index() const
{
	QReadLocker l(&d->m_rwlock);
    return d->m_param->usedBufferIndex;
}

void Dma::set_used_buffer_index(int value)
{
	QWriteLocker l(&d->m_rwlock);
    d->m_param->usedBufferIndex = value;
}

unsigned int Dma::get_scan_source() const
{
	QReadLocker l(&d->m_rwlock);
    return d->m_param->scanSource;
}

void Dma::set_scan_source(int value)
{
	QWriteLocker l(&d->m_rwlock);
    d->m_param->scanSource = value;
}

unsigned int Dma::get_store_frame_count() const
{
	QReadLocker l(&d->m_rwlock);
    return d->m_param->frameCount;
}

void Dma::set_store_frame_count(int value)
{
	QWriteLocker l(&d->m_rwlock);
    d->m_param->frameCount = value;
}

unsigned int Dma::get_encoder_counter_offset() const
{
	QReadLocker l(&d->m_rwlock);
    return d->m_param->encoderOffset;
}

void Dma::set_encoder_counter_offset(int value)
{
	QWriteLocker l(&d->m_rwlock);
    d->m_param->encoderOffset = value;
}

unsigned int Dma::get_steps_per_resolution() const
{
	QReadLocker l(&d->m_rwlock);
    return d->m_param->stepResolution;
}
void Dma::set_steps_per_resolution(int value)
{
	QWriteLocker l(&d->m_rwlock);
    d->m_param->stepResolution = value;
}

unsigned int Dma::get_scan_zero_index_offset() const
{
	QReadLocker l(&d->m_rwlock);
    return d->m_param->scanZeroIndexOffset;
}

void Dma::set_scan_zero_index_offset(int value)
{
	QWriteLocker l(&d->m_rwlock);
    d->m_param->scanZeroIndexOffset = value;
}

unsigned int Dma::get_max_store_index() const
{
	QReadLocker l(&d->m_rwlock);
    return d->m_param->maxStoreIndex;
}
void Dma::set_max_store_index(int value)
{
	QWriteLocker l(&d->m_rwlock);
    d->m_param->maxStoreIndex = value;
}

unsigned int Dma::get_scan_timmer_counter() const
{
	QReadLocker l(&d->m_rwlock);
    return d->m_param->scanTimmerCounter;
}

void Dma::set_scan_timmer_counter(int value)
{
	QWriteLocker l(&d->m_rwlock);
    d->m_param->scanTimmerCounter = value;
}

unsigned int Dma::get_scan_timmer_circled() const
{
	QReadLocker l(&d->m_rwlock);
    return d->m_param->scanTimmerCircled;
}

void Dma::set_scan_timmer_circled(int value)
{
	QWriteLocker l(&d->m_rwlock);
    d->m_param->scanTimmerCircled = value;
}

unsigned char Dma::get_scan_data_mark(int index) const
{
    QReadLocker l(&d->m_rwlock);
    return d->m_scanDataMark[index];
}

Dma *Dma::get_instance()
{
    QMutexLocker locker(&m_mutex);
    if(m_dma == NULL) {
        m_dma = new Dma();
    }
    return m_dma;
}

void Dma::destroyed()
{
    QMutexLocker locker(&m_mutex);
    if(m_dma != NULL) {
        delete m_dma;
        m_dma = NULL;
    }
}

Dma::Dma()
    : d(new DmaPrivate())
{
}

Dma::~Dma()
{
    delete d;
}

}
