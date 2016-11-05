#ifndef SOFTCLIPPEDREAD_H
#define SOFTCLIPPEDREAD_H

#include "ChromosomeRegion.h"
#include "ChromoFragment.h"
#include "CallParams.h"
#include "CallResult.h"
// #include "SingleFragAlnResult.h"
#include "DoubleFragsAlnResult.h"
#include "sequencefetcher.h"


const double MIN_PERCENT_IDENTITY = 95.0;

class ISoftClippedRead
{
public:
    ISoftClippedRead(const std::string &name,
                     const ChromosomeRegion& alignedRegion,
                     const std::string& sequence,
                     int mapQuality,
                     int clippedLength,
                     int smallDelSize,
                     int smallInsSize)
        : name(name),
          alignedRegion(alignedRegion),
          sequence(sequence),
          mapQuality(mapQuality),
          clippedLength(clippedLength),
          smallDelSize(smallDelSize),
          smallInsSize(smallInsSize)
    {}

    virtual ~ISoftClippedRead() {}
    int GetReferenceId() const { return alignedRegion.GetReferenceId(); }
    std::string GetReferenceName() const { return alignedRegion.GetReferenceName(); }
    std::string GetSequence() const { return sequence; }
//    int GetReadLength() const { return sequence.length(); }
    ChromosomeRegion GetAlignedRegion() const { return alignedRegion; }

    virtual GenomePosition GetClipPosition() = 0;

    virtual bool IsAlnResultQualified(DoubleFragsAlnResult *pAlnResult, const CallParams& cParams) = 0;

//    virtual ChromosomeRegionWithCi ToRegionWithCi(const AlignmentResult& aResult, int refStartPos) = 0;

//    virtual CallResult ToCallResult(int refStartPos, const SingleFragAlnResult& alnResult) = 0;

    virtual CallResult *ToCallResult(int refStartPos, DoubleFragsAlnResult *pAlnResult) = 0;

    virtual ChromoFragment CutFragment(const ChromoFragment& cFragment) = 0;

    virtual ChromoFragment ExtendFragment(const ChromoFragment& cFragment, ISequenceFetcher *pSeqFetcher) = 0;

    virtual std::string GetType() = 0;
    virtual std::string GetClippedPart() = 0;

protected:
    std::string name;
    ChromosomeRegion alignedRegion;
    std::string sequence;
    int mapQuality;
    int clippedLength;
    int smallDelSize;
    int smallInsSize;

};

bool IsQualified(int matchLen, int percentIdent, const CallParams& cParams);

int NumOfLongestCommonPrefix(const std::string& v, const std::string& w);

int NumOfLongestCommonSuffix(const std::string& v, const std::string& w);

#endif // SOFTCLIPPEDREAD_H
