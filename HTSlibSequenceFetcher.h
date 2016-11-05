#ifndef HTSLIBSEQUENCEFETCHER_H
#define HTSLIBSEQUENCEFETCHER_H

#include "sequencefetcher.h"
#include "htslib/faidx.h"

class HTSlibSequenceFetcher : public ISequenceFetcher
{
public:
    HTSlibSequenceFetcher(const std::string &fastaFile);
    ~HTSlibSequenceFetcher();
    ChromoFragment Fetch(const ChromosomeRegion& region);

private:
    faidx_t *fai;
};

#endif // HTSLIBSEQUENCEFETCHER_H
