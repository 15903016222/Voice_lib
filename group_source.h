#ifndef __GROUP_SOURCE_H__
#define __GROUP_SOURCE_H__

#include "beam_source.h"

namespace DplSource {

class SOURCESHARED_EXPORT GroupSourcePrivate;

class GroupSource
{
public:
    GroupSource(const char *rawData, int size, int beamNum);

    int beam_num();
    const bool get_beam(int index, BeamSource &beam) const;

private:
    GroupSourcePrivate *d;
};

}

#endif // __GROUP_SOURCE_H__
