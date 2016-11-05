#include "AGERealignWholeReadCaller.h"


ChromoFragment AGERealignWholeReadCaller::PreprocessFragment(ISoftClippedRead *pRead, const ChromoFragment &cFragment)
{
    return pRead->ExtendFragment(cFragment, pSeqFetcher);
}

std::string AGERealignWholeReadCaller::GetSeqFromRead(ISoftClippedRead *pRead)
{
    return pRead->GetSequence();
}

ScoreParam AGERealignWholeReadCaller::MakeScoreParam()
{
    return ScoreParam(2, -3, -2, -5);
}

bool AGERealignWholeReadCaller::IsAlnResultQualified(ISoftClippedRead *pRead, IAlignmentResult *pAlnResult, const CallParams& cParams)
{
    if (!pAlnResult) return false;
    return pRead->IsAlnResultQualified(dynamic_cast<DoubleFragsAlnResult *>(pAlnResult), cParams);
}

CallResult *AGERealignWholeReadCaller::MakeCallResult(ISoftClippedRead *pRead, int refStartPos, IAlignmentResult *pAlnResult)
{
    return pRead->ToCallResult(refStartPos, dynamic_cast<DoubleFragsAlnResult *>(pAlnResult));
}
