#include "Interval.h"
#include <algorithm>


std::ostream& operator <<(std::ostream& stream, const Interval& interval)
{
    stream << "[" << interval.start << "," << interval.end << "]";
    return stream;
}

const Interval operator + (const Interval& one, int x)
{
    Interval result = one;
    result += x;
    return result;
}

void Interval::Flip(int origLength)
{
    int tmp = origLength - start - 1;
    start = origLength - end - 1;
    end = tmp;
    CheckRep();
}

Interval Interval::merge(const Interval &other) const
{
    if (!overlaps(other)) return *this;
    return Interval(std::min(start, other.start), std::max(end, other.end));
}

bool Interval::overlaps(const Interval &other) const
{
    return (start >= other.start && start <= other.end) ||
            (other.start >= start && other.start <= end);
}
