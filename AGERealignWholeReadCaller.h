#ifndef AGEREALIGNWHOLEREADCALLER
#define AGEREALIGNWHOLEREADCALLER

#include "realignmentcaller.h"


class AGERealignWholeReadCaller : public IRealignmentCaller
{
public:
    AGERealignWholeReadCaller(ISequenceAligner *pSeqAligner, ISequenceFetcher *pSeqFetcher)
        : IRealignmentCaller(pSeqAligner, pSeqFetcher)
    {}

    // IRealignmentCaller interface
private:
    ChromoFragment PreprocessFragment(ISoftClippedRead *pRead, const ChromoFragment &cFragment);
    std::string GetSeqFromRead(ISoftClippedRead *pRead);
    ScoreParam MakeScoreParam();
    bool IsAlnResultQualified(ISoftClippedRead *pRead, IAlignmentResult *pAlnResult, const CallParams &cParams);
    CallResult *MakeCallResult(ISoftClippedRead *pRead, int refStartPos, IAlignmentResult *pAlnResult);
};

#endif // AGEREALIGNWHOLEREADCALLER

