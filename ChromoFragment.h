#ifndef CHROMOFRAGMENT
#define CHROMOFRAGMENT

#include "GenomePosition.h"
#include <string>

class ChromoFragment
{
public:
    ChromoFragment(const GenomePosition& start, const std::string& sequence)
        : start(start),
          sequence(sequence)
    {}

    int GetReferenceId() const { return start.GetReferenceId(); }

    std::string GetReferenceName() const { return start.GetReferenceName(); }

    int GetStartPos() const { return start.GetPosition(); }

    int GetLength() const { return sequence.length(); }

    int GetEndPos() const { return GetStartPos() + sequence.length() - 1; }

    GenomePosition GetStart() const { return start; }

    void SetStart(const GenomePosition& newSart) { start = newSart; }

    std::string GetSequence() const { return sequence; }

    void SetSequence(const std::string& newSeq) { sequence = newSeq; }

private:
    GenomePosition start;
    std::string sequence;
};

#endif // CHROMOFRAGMENT

