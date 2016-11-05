#include "softclippedread.h"
#include <algorithm>


bool IsQualified(int matchLen, int percentIdent, const CallParams &cParams)
{
    return matchLen >= cParams.GetMinClip() &&
            percentIdent >= (1 - cParams.GetMaxErrorRate()) * 100;
}

int NumOfLongestCommonPrefix(const std::string &v, const std::string &w)
{

    int n = std::min(v.length(), w.length());
    int i = 0;

    while (i < n && v[i] == w[i])
    {
        i++;
    }

    return i;
}

int NumOfLongestCommonSuffix(const std::string &v, const std::string &w)
{
    std::string v_r(v.rbegin(), v.rend());
    std::string w_r(w.rbegin(), w.rend());

    return NumOfLongestCommonPrefix(v_r, w_r);
}
