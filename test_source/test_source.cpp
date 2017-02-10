#include "test_source.h"

#include "../source.h"
#include <QDebug>

TestSource::TestSource(QObject *parent) :
    QObject(parent),
    m_beamGrp1(new DplSource::BeamGroup(parent)),
    m_beamGrp2(new DplSource::BeamGroup(parent))
{
    m_beamGrp1->set_beam_qty(2);
    m_beamGrp1->set_point_qty(605);

    m_beamGrp2->set_beam_qty(2);
    m_beamGrp2->set_point_qty(605);

    connect(m_beamGrp1, SIGNAL(data_event()), this, SLOT(do_beamgrp1_data_event()));
    connect(m_beamGrp2, SIGNAL(data_event()), this, SLOT(do_beamgrp2_data_event()));
}

void TestSource::start()
{
    DplSource::Source *src = DplSource::Source::get_instance();
    src->set_interval(1);
    src->start();
}

void TestSource::do_beamgrp1_data_event()
{
    qDebug()<<"BeamGroup 1";
    DplSource::BeamPointer beamPtr;
    for (int i = 0; i < m_beamGrp1->beam_qty(); ++i) {
        beamPtr = m_beamGrp1->get(i);
        show_measure(beamPtr);
    }
    qDebug("\n");
}

void TestSource::do_beamgrp2_data_event()
{
    qDebug()<<"BeamGroup 2";
    DplSource::BeamPointer beamPtr;
    for (int i = 0; i < m_beamGrp2->beam_qty(); ++i) {
        beamPtr = m_beamGrp2->get(i);
        show_measure(beamPtr);
    }
    qDebug("\n");
}

void TestSource::show_measure(const DplSource::BeamPointer &beamPtr)
{
    if (beamPtr.isNull()) {
        qDebug()<<__func__<<__LINE__<<"no data";
        return;
    }
    qDebug()<<"Beam Index:"<<beamPtr->index();
    qDebug("Gate A Height(%f) Position(%d)", beamPtr->gate_a_height()/20.47, beamPtr->gate_a_position());
    qDebug("Gate B Height(%f) Position(%d)", beamPtr->gate_b_height()/20.47, beamPtr->gate_b_position());
    qDebug("Gate I Height(%f) Position(%d)", beamPtr->gate_i_height()/20.47, beamPtr->gate_i_position());
    qDebug("Encoder x:y(%d, %d)", beamPtr->encoder_x(), beamPtr->encoder_y());
}
