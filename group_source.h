#ifndef __GROUP_SOURCE_H__
#define __GROUP_SOURCE_H__

#include "beam_source.h"

namespace DplSource {

class SOURCESHARED_EXPORT GroupSourcePrivate;

class GroupSource
{
public:
    GroupSource(int beamNum, int pointNum);
    ~GroupSource();

    void set_raw_data(const char *rawData);

    void set_beam_number(int number);
    int beam_number();
    void set_point_number(int number);
    int point_number();

    int size();

    bool get_beam(int beamNo, BeamSource &beam) const;

private:
    GroupSourcePrivate *d;
};

}

#endif // __GROUP_SOURCE_H__
