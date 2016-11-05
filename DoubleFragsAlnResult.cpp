#include "DoubleFragsAlnResult.h"

#include <algorithm>


void DoubleFragsAlnResult::PrintAlignment()
{
    alnFrag1.PrintAlignment();
    std::cout << "<EXCISED REGION>" << std::endl;
    alnFrag2.PrintAlignment();
}

double DoubleFragsAlnResult::GetPercentIdentity()
{
    return 100.0f*(alnFrag1.NumOfIdenticalBases() + alnFrag2.NumOfIdenticalBases()) / (alnFrag1.GetAlignmentLength() + alnFrag2.GetAlignmentLength());
}

void DoubleFragsAlnResult::Flip()
{
    std::reverse(v.begin(), v.end());
    std::reverse(w.begin(), w.end());

    int l_v = v.length();
    int l_w = w.length();

    alnFrag1.Flip(l_v, l_w);

    alnFrag2.Flip(l_v, l_w);
}

//int AlignmentResult::NumOfHomToRight() const
//{
//    if (single) return 0;

//    int e1 = aFragment1.GetMatch1().GetEnd();
//    int s2 = aFragment2.GetMatch1().GetStart();

//    std::string v = seq1.substr(e1 + 1, s2 - e1);
//    std::string w = seq1.substr(s2);

//    return NumOfLongestCommonPrefix(v, w);
//}
