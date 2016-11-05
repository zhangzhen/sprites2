#ifndef FIVEENDREVERSESCREAD_H
#define FIVEENDREVERSESCREAD_H

#include "softclippedread.h"

class FiveEndReverseSCRead : public ISoftClippedRead
{
public:
    FiveEndReverseSCRead(const std::string &name,
                         const ChromosomeRegion& alignedRegion,
                         const std::string &sequence,
                         int mapQuality,
                         int clippedLength,
                         int smallDelSize,
                         int smallInsSize);

    GenomePosition GetClipPosition();

    std::string GetType();

    std::string GetClippedPart();

    ChromoFragment CutFragment(const ChromoFragment &cFragment);

    ChromoFragment ExtendFragment(const ChromoFragment &cFragment, ISequenceFetcher *pSeqFetcher);

//    ChromosomeRegionWithCi ToRegionWithCi(const AlignmentResult& aResult, int refStartPos);

    bool IsAlnResultQualified(DoubleFragsAlnResult *pAlnResult, const CallParams &cParams);

    CallResult *ToCallResult(int refStartPos, DoubleFragsAlnResult *pAlnResult);
};

#endif // FIVEENDREVERSESCREAD_H
