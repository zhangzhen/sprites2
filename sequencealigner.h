#ifndef SEQUENCEALIGNER_H
#define SEQUENCEALIGNER_H

#include "alignmentresult.h"
#include "ScoreParam.h"

class ISequenceAligner
{
public:
    virtual ~ISequenceAligner() {}
    virtual IAlignmentResult* Align(const std::string& v, const std::string& w, const ScoreParam &sParam) = 0;
};

#endif // SEQUENCEALIGNER_H
