#ifndef SEQUENCEFETCHER_H
#define SEQUENCEFETCHER_H

#include "ChromosomeRegion.h"
#include "ChromoFragment.h"


class ISequenceFetcher
{
public:
    virtual ~ISequenceFetcher() {}
    virtual ChromoFragment Fetch(const ChromosomeRegion& region) = 0;
};

#endif // SEQUENCEFETCHER_H
