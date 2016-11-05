#include "FiveEndForwardSCRead.h"
#include "Deletion.h"


FiveEndForwardSCRead::FiveEndForwardSCRead(const std::string &name,
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

GenomePosition FiveEndForwardSCRead::GetClipPosition()
{
    return alignedRegion.GetStart();
}

std::string FiveEndForwardSCRead::GetType()
{
    return "5F";
}

std::string FiveEndForwardSCRead::GetClippedPart()
{
    return sequence.substr(0, clippedLength);
}

ChromoFragment FiveEndForwardSCRead::CutFragment(const ChromoFragment &cFragment)
{
    if (GetReferenceId() != cFragment.GetReferenceId())
    {
        error("This fragment cannot be cut because the fragment and the read are not on the same chromosome.");
    }

    int pos1 = cFragment.GetEndPos();

    int pos2 = GetClipPosition().GetPosition();

    if (pos2 <= pos1)
    {
        int removedLen = pos1 - pos2 + 1;

        return ChromoFragment(cFragment.GetStart(), cFragment.GetSequence().substr(0, cFragment.GetLength() - removedLen));
    }

    return cFragment;
}

ChromoFragment FiveEndForwardSCRead::ExtendFragment(const ChromoFragment &cFragment, ISequenceFetcher *pSeqFetcher)
{
    int t1 = cFragment.GetEndPos();

    int c0 = alignedRegion.GetStartPosition();
    int c1 = alignedRegion.GetEndPosition();
    int cx = c0 - clippedLength;

    if (t1 >= c1)
    {
        return cFragment;
    }

    std::string extSeq = (t1 < cx) ?
                pSeqFetcher->Fetch(ChromosomeRegion(GetReferenceId(), GetReferenceName(), cx, c1)).GetSequence() :
                pSeqFetcher->Fetch(ChromosomeRegion(GetReferenceId(), GetReferenceName(), t1 + 1, c1)).GetSequence();

    ChromoFragment newFrag = cFragment;

    newFrag.SetSequence(newFrag.GetSequence() + extSeq);

    return newFrag;
}

//ChromosomeRegionWithCi FiveEndForwardSCRead::ToRegionWithCi(const AlignmentResult &aResult, int refStartPos)
//{
//    GenomePosition clipPosition = GetClipPosition();

//    int nHom = aResult.NumOfHomToRight();

//    int delta = clippedLength - aResult.GetAlignmentFragment1().GetMatch2().GetEnd() -nHom - 1;

//    int endPos = clipPosition.GetPosition();

//    int startPos = aResult.GetAlignmentFragment1().GetMatch1().GetEnd() + nHom + refStartPos;

//    Interval cInterval;

//    if (delta < 0)
//    {
//        startPos += delta;
//        cInterval = Interval(0, abs(delta));
//    }

//    if (!aResult.HasSingleFragment())
//    {
//        int f2_l1 = aResult.GetAlignmentFragment2().GetMatch1().Length();
//        int f2_d = refSeqPart.length() - f2_l1;
//        if (f2_d > 0)
//            endPos += f2_d;
//    }

//    return ChromosomeRegionWithCi(GetReferenceId(),
//                                  GetReferenceName(),
//                                  startPos,
//                                  cInterval,
//                                  endPos,
//                                  cInterval);
//}

bool FiveEndForwardSCRead::IsAlnResultQualified(DoubleFragsAlnResult *pAlnResult, const CallParams &cParams)
{
    return IsQualified(pAlnResult->GetAlnFrag1LengthW(), pAlnResult->GetAlnFrag1PercentIdentity(), cParams);
}

CallResult *FiveEndForwardSCRead::ToCallResult(int refStartPos, DoubleFragsAlnResult *pAlnResult)
{
    int f1_e_v = pAlnResult->GetAlnFrag1EndV();
    int f2_s_v = pAlnResult->GetAlnFrag2StartV();

    int startPos = refStartPos + f1_e_v;
    int endPos = GetClipPosition().GetPosition();

    int f2_l1 = pAlnResult->GetAlnFrag2LengthV();
    int f2_d = alignedRegion.GetLength() - f2_l1;

    endPos += f2_d;

    Interval cInterval;

    std::string microIns = "";

    int n_bases = pAlnResult->NumOfWBasesBetweenTwoFrags();

    std::string v = pAlnResult->GetV();

    if (n_bases > 0)
    {
        std::string v1 = v.substr(f2_s_v - n_bases, n_bases);
        std::string w = pAlnResult->WBasesBetweenTwoFrags();
        int n_mismatch1 = n_bases - NumOfIdenticalChars(v1, w);

        std::string v2 = v.substr(f1_e_v + 1, n_bases);
        int n_mismatch2 = n_bases - NumOfIdenticalChars(v2, w);

        if (n_mismatch1 <= 1)
        {
            endPos -= n_bases;
            f2_s_v -= n_bases;
        }
        else if (n_mismatch2 <= 1)
        {
            startPos += n_bases;
            f1_e_v += n_bases;
        }
        else
        {
            microIns = v;
        }

        if (n_mismatch1 <= 1 && n_mismatch2 <= 1)
        {
            cInterval.SetEnd(n_bases);
        }
    }

    if (startPos >= endPos)
    {
        return NULL;
    }

    std::string s1 = v.substr(f2_s_v);
    std::string t1 = v.substr(f1_e_v + 1, s1.length());

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
