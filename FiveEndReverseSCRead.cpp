#include "FiveEndReverseSCRead.h"


FiveEndReverseSCRead::FiveEndReverseSCRead(const std::string &name,
                                           const ChromosomeRegion &alignedRegion,
                                           const std::string &sequence,
                                           int mapQuality,
                                           int clippedLength,
                                           int smallDelSize,
                                           int smallInsSize)
    : ISoftClippedRead(name,
                       alignedRegion,
                       sequence,
                       mapQuality,
                       clippedLength,
                       smallDelSize,
                       smallInsSize)
{
}

GenomePosition FiveEndReverseSCRead::GetClipPosition()
{
    return alignedRegion.GetEnd();
}


std::string FiveEndReverseSCRead::GetType()
{
    return "5R";
}

std::string FiveEndReverseSCRead::GetClippedPart()
{
    return sequence.substr(sequence.length() - clippedLength);
}

ChromoFragment FiveEndReverseSCRead::CutFragment(const ChromoFragment &cFragment)
{
    if (GetReferenceId() != cFragment.GetReferenceId())
    {
        error("This fragment cannot be cut because the fragment and the read are not on the same chromosome.");
    }

    int pos1 = cFragment.GetStartPos();

    int pos2 = GetClipPosition().GetPosition();

    if (pos1 <= pos2)
    {
        return ChromoFragment(GenomePosition(GetReferenceId(), GetReferenceName(), pos2),
                              cFragment.GetSequence().substr(pos2 - pos1 + 1));
    }

    return cFragment;
}

ChromoFragment FiveEndReverseSCRead::ExtendFragment(const ChromoFragment &cFragment, ISequenceFetcher *pSeqFetcher)
{
    if (GetReferenceId() != cFragment.GetReferenceId())
    {
        error("This fragment cannot be cut because the fragment and the read are not on the same chromosome.");
    }

    int t0 = cFragment.GetStartPos();

    int c0 = alignedRegion.GetStartPosition();
    int c1 = alignedRegion.GetEndPosition();
    int cx = c1 + clippedLength;

    if (t0 <= c0)
    {
        return cFragment;
    }

    std::string extSeq = (t0 > cx) ?
                pSeqFetcher->Fetch(ChromosomeRegion(GetReferenceId(), GetReferenceName(), c0, cx)).GetSequence() :
                pSeqFetcher->Fetch(ChromosomeRegion(GetReferenceId(), GetReferenceName(), c0, t0 - 1)).GetSequence();

    ChromoFragment newFrag = cFragment;

    newFrag.SetStart(newFrag.GetStart() - extSeq.length());
    newFrag.SetSequence(extSeq + newFrag.GetSequence());

    return newFrag;
}

//ChromosomeRegionWithCi FiveEndReverseSCRead::ToRegionWithCi(const AlignmentResult &aResult, int refStartPos)
//{
//    int s1 = aResult.GetAlignmentFragment1().GetMatch1().GetStart() + refStartPos;
//    int s2 = aResult.GetAlignmentFragment1().GetMatch2().GetStart();

//    if (!aResult.HasSingleFragment())
//    {
//        s1 = aResult.GetAlignmentFragment2().GetMatch1().GetStart() + refStartPos;
//        s2 = aResult.GetAlignmentFragment2().GetMatch2().GetStart();
//    }

//    int delta = s2 - GetSequence().length() + clippedLength;

//    int startPos = GetClipPosition().GetPosition();

//    int endPos = s1;

//    Interval cInterval;

//    if (delta < 0)
//    {
//        startPos += delta;
//        cInterval = Interval(0, abs(delta));
//    }

//    return ChromosomeRegionWithCi(GetReferenceId(),
//                                  GetReferenceName(),
//                                  startPos,
//                                  cInterval,
//                                  endPos,
//                                  cInterval);
//}

bool FiveEndReverseSCRead::IsAlnResultQualified(DoubleFragsAlnResult *pAlnResult, const CallParams &cParams)
{
    return IsQualified(pAlnResult->GetAlnFrag2LengthW(), pAlnResult->GetAlnFrag2PercentIdentity(), cParams);
}

CallResult *FiveEndReverseSCRead::ToCallResult(int refStartPos, DoubleFragsAlnResult *pAlnResult)
{
    int f1_e_v = pAlnResult->GetAlnFrag1EndV();
    int f2_s_v = pAlnResult->GetAlnFrag2StartV();

    int startPos = GetClipPosition().GetPosition();
    int endPos = refStartPos + f2_s_v;

    int f1_l1 = pAlnResult->GetAlnFrag1LengthV();

    int f1_d = alignedRegion.GetLength() - f1_l1;

    startPos -= f1_d;

    Interval cInterval;

    std::string microIns = "";

    int n_bases = pAlnResult->NumOfWBasesBetweenTwoFrags();

    std::string v = pAlnResult->GetV();

    if (n_bases > 0)
    {
        std::string v1 = v.substr(f1_e_v + 1, n_bases);
        std::string w = pAlnResult->WBasesBetweenTwoFrags();
        int n_mismatch1 = n_bases - NumOfIdenticalChars(v1, w);

        std::string v2 = v.substr(f2_s_v - n_bases, n_bases);
        int n_mismatch2 = n_bases - NumOfIdenticalChars(v2, w);

        if (n_mismatch1 <= 1)
        {
            startPos += n_bases;
            f1_e_v += n_bases;
        }
        else if (n_mismatch2 <= 1)
        {
            endPos -= n_bases;
            f2_s_v -= n_bases;
        }
        else
        {
            microIns = v;
        }

        if (n_mismatch1 <= 1 && n_mismatch2 <= 1)
        {
            cInterval.SetStart(-n_bases);
        }

    }

    if (startPos >= endPos)
    {
        return NULL;
    }

    std::string s1 = v.substr(f2_s_v);
    std::string t1 = v.substr(f1_e_v + 1, s1.length());

//    if (GetClipPosition().GetPosition() == 10111162)
//    {
//        std::cout << s1 << std::endl;
//        std::cout << t1 << std::endl;
//    }

    int nr = NumOfLongestCommonPrefix(s1, t1);
    std::string micro_hom_r = v.substr(f2_s_v, nr);

    std::string s2 = v.substr(0, f1_e_v);
    std::string t2 = v.substr(f2_s_v - s2.length(), s2.length());

    int nl = NumOfLongestCommonSuffix(s2, t2);
    std::string micro_hom_l = v.substr(f1_e_v - nl, nl);

    cInterval = cInterval.merge(Interval(-nl, nr));


    return new CallResult(ChromosomeRegion(GetReferenceId(),
                                       GetReferenceName(),
                                       startPos,
                                       endPos),
                          cInterval,
                          cInterval,
                      microIns,
                          micro_hom_l + micro_hom_r);
}
