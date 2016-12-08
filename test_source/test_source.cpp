#include "test_source.h"
#include <QDebug>

TestSource::TestSource(QObject *parent) : QObject(parent)
{
    m_source = DplSource::Source::get_instance();
    m_source->create_group(16, 605);
    connect(m_source, SIGNAL(data_event()), this, SLOT(do_source_data_event()));
}

void TestSource::start()
{
    m_source->set_interval(1000);
    m_source->set_freeze(false);
}

void TestSource::do_source_data_event()
{
    qDebug()<<__func__<<__LINE__;
    DplSource::GroupSourcePointer groupPointer = m_source->get_group(0);
    qDebug()<<__func__<<__LINE__;
    DplSource::BeamSource beam;
    qDebug()<<__func__<<__LINE__;
    if ( ! groupPointer->get_beam(0, beam) ) {
        qDebug()<<__func__<<__LINE__;
        return;
    }
    qDebug("beam:%d point:%d", groupPointer->beam_number(), beam.point_qty());
    qDebug()<<"Gate A Height:"<<beam.gate_a_height()/(20.47);
    qDebug()<<"x:y="<<beam.encoder_x()<<beam.encoder_y();
}
