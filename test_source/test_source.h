#ifndef __TEST_SOURCE_H__
#define __TEST_SOURCE_H__

#include <QObject>

#include "../source.h"

class TestSource : public QObject
{
    Q_OBJECT
public:
    explicit TestSource(QObject *parent = 0);
    void start();

signals:

public slots:
    void do_source_data_event();

private:
    DplSource::Source *m_source;

    void show_measure(const DplSource::BeamSource &beam);
};

#endif // __TEST_SOURCE_H__
