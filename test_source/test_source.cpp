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
    m_source->set_interval(1);
    m_source->set_freeze(false);
}

void TestSource::do_source_data_event()
{
    DplSource::GroupSourcePointer groupPointer;/* = m_source->get_group(0);*/
    DplSource::BeamSource beam;

    for (int i = 0; i < m_source->groups(); ++i) {
        groupPointer = m_source->get_group(0);
        qDebug()<<"Beam Information("<<groupPointer->beam_number()<<")";
        for (int j = 0; j < groupPointer->beam_number(); ++j) {
            if ( ! groupPointer->get_beam(j, beam) ) {
                qDebug()<<"out";
                return;
            }
            show_measure(beam);
        }
        qDebug("\n\n");
    }
}

void TestSource::show_measure(const DplSource::BeamSource &beam)
{
    qDebug()<<"Beam Index:"<<beam.index();
    qDebug("Gate A Height(%f) Position(%d)", beam.gate_a_height()/20.47, beam.gate_a_position());
    qDebug("Gate B Height(%f) Position(%d)", beam.gate_b_height()/20.47, beam.gate_b_position());
    qDebug("Gate I Height(%f) Position(%d)", beam.gate_i_height()/20.47, beam.gate_i_position());
    qDebug("Encoder x:y(%d, %d)", beam.encoder_x(), beam.encoder_y());
}
