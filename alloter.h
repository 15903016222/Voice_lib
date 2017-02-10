#ifndef __ALLOTER_H__
#define __ALLOTER_H__

#include <QObject>
#include <QMutex>
#include "beam_group.h"

namespace DplSource {

class Alloter : public QObject
{
    Q_OBJECT
public:
    static Alloter *get_instance();
    static void destroyed();

    void add(BeamGroup *beams);
    void remove(BeamGroup *beams);

signals:

public slots:
    void do_data_event(const char *data);

protected:
    explicit Alloter(QObject *parent = 0);

private:
    static QMutex s_mutex;
    static Alloter *s_instance;

    QList<BeamGroup *> m_beamGroups;
};

}

#endif // __ALLOTER_H__
