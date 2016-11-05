#ifndef AGEALIGNERADAPTER_H
#define AGEALIGNERADAPTER_H

#include "sequencealigner.h"


class AGEAlignerAdapter : public ISequenceAligner
{
public:
    AGEAlignerAdapter() {}

    IAlignmentResult *Align(const std::string& v, const std::string& w, const ScoreParam &sParam);
};

#endif // AGEALIGNERADAPTER_H
