#include "test_source.h"

#include <QDebug>

TestSource::TestSource(QObject *parent) :
    QObject(parent),
    m_source(DplSource::Source::instance())
{
    m_source->register_group(0, 1, 605);

    connect(m_source, SIGNAL(data_event()),
            this, SLOT(do_data_event()),
            Qt::DirectConnection);
}

void TestSource::start()
{
    DplSource::Source *src = DplSource::Source::instance();
    src->start();
}

void TestSource::do_data_event()
{
    DplSource::BeamsPointer beamsPtr = m_source->current_beams(0);
    show_measure(beamsPtr->get(0));
}

void TestSource::show_measure(const DplSource::BeamPointer &beamPtr)
{
    if (beamPtr.isNull()) {
        qDebug()<<__func__<<__LINE__<<"no data";
        return;
    }
    qDebug()<<"Beam Index:"<<beamPtr->index();
    qDebug("Gate A Height(%f) Position(%d)",
           beamPtr->gate_peak(DplSource::Beam::GATE_A)/20.47,
           beamPtr->gate_peak_position(DplSource::Beam::GATE_A));
    qDebug("Gate B Height(%f) Position(%d)",
           beamPtr->gate_peak(DplSource::Beam::GATE_B)/20.47,
           beamPtr->gate_peak_position(DplSource::Beam::GATE_B));
    qDebug("Gate I Height(%f) Position(%d)",
           beamPtr->gate_peak(DplSource::Beam::GATE_I)/20.47,
           beamPtr->gate_peak_position(DplSource::Beam::GATE_I));
    qDebug("Encoder x:y(%d, %d)", beamPtr->encoder_x(), beamPtr->encoder_y());
}
