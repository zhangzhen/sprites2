#ifndef INTERVAL_H
#define INTERVAL_H

#include <cassert>
#include <iostream>

class Interval
{
public:
    Interval(int start, int end)
        : start(start),
          end(end)
    {
        CheckRep();
    }

    Interval()
        : Interval(0, 0)
    {}

    int GetStart() const { return start; }
    int GetEnd() const { return end; }
    int Length() const { return end - start + 1; }

    void SetStart(int newStart)
    {
        assert(newStart <= end);
        start = newStart;
    }
    void SetEnd(int newEnd)
    {
        assert(start <= newEnd);
        end = newEnd;
    }

    Interval& operator += (int x)
    {
        start += x;
        end += x;
        return *this;
    }

    bool operator == (const Interval& other) const
    {
        return start == other.start && end == other.end;
    }

    bool operator != (const Interval& other) const
    {
        return !(*this == other);
    }

    void Flip(int origLength);

    Interval merge(const Interval &other) const;

    bool overlaps(const Interval &other) const;

    friend std::ostream& operator <<(std::ostream& stream, const Interval& interval);

private:
    int start;
    int end;

    void CheckRep()
    {
        assert(start <= end);
    }
};

const Interval operator + (const Interval& one, int x);


#endif // INTERVAL_H
