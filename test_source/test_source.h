#ifndef __TEST_SOURCE_H__
#define __TEST_SOURCE_H__

#include <QObject>

#include "beam_group.h"

class TestSource : public QObject
{
    Q_OBJECT
public:
    explicit TestSource(QObject *parent = 0);
    void start();

signals:

public slots:
    void do_beamgrp1_data_event();
    void do_beamgrp2_data_event();

private:
    DplSource::BeamGroup *m_beamGrp1;
    DplSource::BeamGroup *m_beamGrp2;

    void show_measure(const DplSource::BeamPointer &beam);
};

#endif // __TEST_SOURCE_H__
