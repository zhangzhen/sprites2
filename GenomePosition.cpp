#include "GenomePosition.h"

using namespace std;

GenomePosition::GenomePosition(int referenceId, const string &referenceName, int position)
    : referenceId(referenceId),
      referenceName(referenceName),
      position(position)
{
}

ostream &operator <<(ostream &stream, const GenomePosition &gPos)
{
    stream << gPos.referenceName
           << ":" << gPos.position;
    return stream;
}

const GenomePosition operator +(const GenomePosition &one, int x)
{
    GenomePosition result = one;
    result += x;
    return result;
\
}

const GenomePosition operator -(const GenomePosition &one, int x)
{
    return one + (-x);
}
