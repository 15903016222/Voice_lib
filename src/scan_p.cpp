#include "scan_p.h"

namespace DplSource {

ScanPrivate::ScanPrivate(Scan *parent) :
    m_speed(20.0),
    m_encX(new Encoder),
    m_encY(new Encoder),
    m_scanAxis(new Axis),
    m_indexAxis(new Axis),
    m_mode(Scan::ONELINE),
    q_ptr(parent)
{
    connect(static_cast<DplSource::Axis *>(m_scanAxis.data()),
            SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this, SLOT(do_scanAxis_driving_changed(DplSource::Axis::Driving)));

    connect(static_cast<DplSource::Axis *>(m_indexAxis.data()),
            SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this, SLOT(do_indexAxis_driving_changed(DplSource::Axis::Driving)));
}

void ScanPrivate::set_mode(Scan::Mode mode)
{
    if (m_mode == mode) {
        return;
    }

    m_mode = mode;

    if (mode == Scan::ONELINE) {
        m_scanAxis->set_driving(Axis::TIMER);
        m_indexAxis->set_driving(Axis::NONE);
        m_encX->set_enabled(false);
        m_encY->set_enabled(false);
    } else {
        m_scanAxis->set_driving(Axis::ENCODER_X);
        m_indexAxis->set_driving(Axis::ENCODER_Y);
        m_encX->set_enabled(true);
        m_encY->set_enabled(true);
    }

    emit q_ptr->mode_changed(m_mode);
}

void ScanPrivate::do_scanAxis_driving_changed(Axis::Driving driving)
{
    if (m_mode == Scan::ONELINE) {
        if (driving == Axis::TIMER) {
            m_encX->set_enabled(false);
            m_encY->set_enabled(false);
        } else if (driving == Axis::ENCODER_X) {
            m_encX->set_enabled(true);
            m_encY->set_enabled(false);
        } else if (driving == Axis::ENCODER_Y) {
            m_encX->set_enabled(false);
            m_encY->set_enabled(true);
        }
    } else {
        if (driving == Axis::ENCODER_X) {
            m_indexAxis->set_driving(Axis::ENCODER_Y);
        } else if (driving == Axis::ENCODER_Y) {
            m_indexAxis->set_driving(Axis::ENCODER_X);
        }
    }
}

void ScanPrivate::do_indexAxis_driving_changed(Axis::Driving driving)
{
    if (driving == Axis::ENCODER_X) {
        m_scanAxis->set_driving(Axis::ENCODER_Y);
    } else if (driving == Axis::ENCODER_Y) {
        m_scanAxis->set_driving(Axis::ENCODER_X);
    }
}

}
