#ifndef __TEST_SOURCE_H__
#define __TEST_SOURCE_H__

#include <QObject>

#include "source.h"

class TestSource : public QObject
{
    Q_OBJECT
public:
    explicit TestSource(QObject *parent = 0);
    void start();

signals:

public slots:
    void do_data_event();

private:
    void show_measure(const DplSource::BeamPointer &beam);

    DplSource::Source *m_source;
};

#endif // __TEST_SOURCE_H__
