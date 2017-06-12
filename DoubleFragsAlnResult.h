#ifndef DOUBLEFRAGSALNRESULT
#define DOUBLEFRAGSALNRESULT

#include "alignmentresult.h"
#include "AlignmentFragment.h"


class DoubleFragsAlnResult : public IAlignmentResult
{
public:
    DoubleFragsAlnResult(const std::string& v,
                         const std::string& w,
                         int score,
                         const AlignmentFragment& alnFrag1,
                         const AlignmentFragment& alnFrag2)
        : IAlignmentResult(v, w, score),
          alnFrag1(alnFrag1),
          alnFrag2(alnFrag2)
    {}

    int GetAlnFrag1EndV() const
    {
        return alnFrag1.GetMatch1().GetEnd();
    }

    int GetAlnFrag2StartV() const
    {
        return alnFrag2.GetMatch1().GetStart();
    }

    int GetAlnFrag1EndW() const
    {
        return alnFrag1.GetMatch2().GetEnd();
    }

    int GetAlnFrag2StartW() const
    {
        return alnFrag2.GetMatch2().GetStart();
    }

    int GetAlnFrag1LengthV() const
    {
        return alnFrag1.GetMatch1().Length();
    }

    int GetAlnFrag1LengthW() const
    {
        return alnFrag1.GetMatch2().Length();
    }

    int GetAlnFrag2LengthV() const
    {
        return alnFrag2.GetMatch1().Length();
    }

    int GetAlnFrag2LengthW() const
    {
        return alnFrag2.GetMatch2().Length();
    }

//    std::string GetAlnFrag1AlignedW() const
//    {
//        return alnFrag1.GetAlignedS2();
//    }

    double GetAlnFrag1PercentIdentity() const
    {
        return alnFrag1.GetPercentageIdentity();
    }

    double GetAlnFrag2PercentIdentity() const
    {
        return alnFrag2.GetPercentageIdentity();
    }

    AlignmentFragment GetAlnFrag1() const { return alnFrag1; }
    AlignmentFragment GetAlnFrag2() const { return alnFrag2; }

    int NumOfWBasesBetweenTwoFrags() const
    {
        return GetAlnFrag2StartW() - GetAlnFrag1EndW() - 1;
    }

	int NumOfVBasesBetweenTwoFrags() const
	{
		return GetAlnFrag2StartV() - GetAlnFrag1EndV() - 1;
	}

    std::string WBasesBetweenTwoFrags() const
    {
        return WBasesBetweenTwoFragsExtLeft(0);
    }

    std::string WBasesBetweenTwoFragsExtLeft(int shift) const
    {
        assert(shift >= 0);
        int n_bases = NumOfWBasesBetweenTwoFrags();
        if (n_bases == 0) return "";
        return w.substr(GetAlnFrag1EndW() + 1 - shift, n_bases + shift);
    }

private:
    AlignmentFragment alnFrag1;
    AlignmentFragment alnFrag2;

    // IAlignmentResult interface
public:
    void PrintAlignment();
    double GetPercentIdentity();

    void Flip();
};

#endif // DOUBLEFRAGSALNRESULT

