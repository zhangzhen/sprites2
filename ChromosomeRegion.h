#ifndef CHROMOSOMEREGION_H
#define CHROMOSOMEREGION_H

#include "GenomePosition.h"
#include "Interval.h"
#include <iostream>

class ChromosomeRegion
{
public:
    ChromosomeRegion(int referenceId,
                     const std::string& referenceName,
                     int startPos,
                     int endPos);
    int GetReferenceId() const { return referenceId; }
    std::string GetReferenceName() const { return referenceName; }
    GenomePosition GetStart() const { return GenomePosition(referenceId, referenceName, interval.GetStart()); }
    GenomePosition GetEnd() const { return GenomePosition(referenceId, referenceName, interval.GetEnd()); }

    int GetStartPosition() const { return interval.GetStart(); }
    int GetEndPosition() const { return interval.GetEnd(); }

    int GetLength() const { return interval.Length(); }

    Interval GetInterval() const { return interval; }

    ChromosomeRegion *Merge(const ChromosomeRegion &other);

    void CutHead(int newPos)
    {
        if (newPos > interval.GetStart())
        {
            interval.SetStart(newPos);
        }
    }

    void CutTail(int newPos)
    {
        if (newPos < interval.GetEnd())
        {
            interval.SetEnd(newPos);
        }
    }

    friend std::ostream &operator <<(std::ostream& stream, const ChromosomeRegion& cRegion);
    friend bool operator == (const ChromosomeRegion& one, const ChromosomeRegion& two);

private:
    int referenceId;
    std::string referenceName;
    Interval interval;
};

#endif // CHROMOSOMEREGION_H
