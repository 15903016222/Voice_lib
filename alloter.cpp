#include "alloter.h"
#include "dma.h"
#include "source.h"

namespace DplSource {

QMutex Alloter::s_mutex;
Alloter *Alloter::s_instance = NULL;

Alloter *Alloter::get_instance()
{
    QMutexLocker l(&s_mutex);
    if (s_instance == NULL) {
        s_instance = new Alloter();
    }
    return s_instance;
}

void Alloter::destroyed()
{
    QMutexLocker l(&s_mutex);
    if (s_instance != NULL) {
        delete s_instance;
        s_instance = NULL;
    }
}

void Alloter::add(BeamGroup *beams)
{
    QMutexLocker l(&s_mutex);
    m_beamGroups.append(beams);
}

void Alloter::remove(BeamGroup *beams)
{
    QMutexLocker l(&s_mutex);
    m_beamGroups.removeAll(beams);
}

void Alloter::do_data_event(const char *data)
{
    QMutexLocker l(&s_mutex);
    int offset = 0;
    for (int i = 0; i < m_beamGroups.size(); ++i) {
        m_beamGroups[i]->set_raw_data(data + offset);
        offset += m_beamGroups[i]->size();
    }
}

Alloter::Alloter(QObject *parent) :
    QObject(parent)
{
    Source *source = Source::get_instance();
    connect(source, SIGNAL(data_event(const char*)),
            this, SLOT(do_data_event(const char*)));
}

}
