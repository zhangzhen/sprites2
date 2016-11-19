#include "AlignmentFragment.h"

#include <algorithm>


int AlignmentFragment::NumOfIdenticalBases() const
{
	//std::cout << alignedS1 << std::endl;
	//std::cout << alignedS2 << std::endl;
    return NumOfIdenticalChars(alignedS1, alignedS2);
}

void AlignmentFragment::PrintAlignment() const
{
    std::cout << match1 << " to " << match2 << std::endl;
    std::cout << alignedS1 << std::endl;
    std::cout << alignedS2 << std::endl;
}

void AlignmentFragment::Flip(int origLength1, int origLength2)
{
    std::reverse(alignedS1.begin(), alignedS1.end());
    std::reverse(alignedS2.begin(), alignedS2.end());
    match1.Flip(origLength1);
    match2.Flip(origLength2);
}

bool AlignmentFragment::operator ==(const AlignmentFragment &other) const
{
    return alignedS1 == other.alignedS1 &&
            alignedS2 == other.alignedS2 &&
            match1 == other.match1 &&
            match2 == other.match2;
}

int NumOfIdenticalChars(const std::string &v, const std::string &w)
{
    assert(v.length() == w.length());

    int s = 0;
    for (size_t i = 0; i < v.length(); ++i)
    {
        if (v[i] == w[i]) s++;
    }
    return s;
}

bool IsLastCharIdentical(const std::string &v, const std::string &w)
{
    return v.back() == w.back();
}
