/**
 * @file alloter.cpp
 * @brief 分配器，分配各BeamGroup的数据资源
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2017-02-10
 */
#include "alloter.h"
#include "dma.h"
#include "source.h"

namespace DplSource {

Alloter *Alloter::instance()
{
    static Alloter *instance = new Alloter();
    return instance;
}

void Alloter::add(BeamGroup *beams)
{
    {
        QWriteLocker l(&m_rwlock);
        m_beamGroups.append(beams);
        connect(beams, SIGNAL(beam_qty_changed(int)), this, SLOT(do_beam_group_changed()));
        connect(beams, SIGNAL(point_qty_changed(int)), this, SLOT(do_beam_group_changed()));
    }
    do_beam_group_changed();
}

void Alloter::remove(BeamGroup *beams)
{
    {
        QWriteLocker l(&m_rwlock);
        m_beamGroups.removeAll(beams);
    }
    do_beam_group_changed();
}

void Alloter::do_data_event(const char *data)
{
    int offset = 0;
    QReadLocker l(&m_rwlock);
    for (int i = 0; i < m_beamGroups.size(); ++i) {
        m_beamGroups[i]->set_raw_data(data + offset);
        offset += m_beamGroups[i]->size();
    }
}

void Alloter::do_beam_group_changed()
{
    int size = 0;
    for (int i = 0; i < m_beamGroups.size(); ++i) {
        size += m_beamGroups[i]->size();
    }

    Dma *dma = Dma::instance();
    if (dma) {
        dma->set_frame_size(size);
    }
}

Alloter::Alloter(QObject *parent) :
    QObject(parent)
{
    Source *source = Source::instance();
    connect(source, SIGNAL(data_event(const char*)),
            this, SLOT(do_data_event(const char*)));
}

}
