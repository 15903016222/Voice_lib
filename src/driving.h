#ifndef __DPLSOURCE_DRIVING_H__
#define __DPLSOURCE_DRIVING_H__

#include "source_global.h"
#include <QSharedPointer>

namespace DplSource {

class SOURCESHARED_EXPORT Driving : public QObject
{
    Q_OBJECT
public:
    explicit Driving(QObject *parent = 0);

    enum Type {
        TIMER,
        ENCODER,
    };

    virtual Type type() const { return TIMER; }
};

typedef QSharedPointer<Driving> DrivingPointer;

}

#endif // __DPLSOURCE_DRIVING_H__
