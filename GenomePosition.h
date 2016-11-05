#ifndef GENOMEPOSITION_H
#define GENOMEPOSITION_H

#include <iostream>

class GenomePosition
{
public:
    GenomePosition(int referenceId, const std::string& referenceName, int position);

    GenomePosition() : GenomePosition(-1, "NA", 0) {}

    int GetReferenceId() const { return referenceId; }

    std::string GetReferenceName() const { return referenceName; }
    int GetPosition() const { return position; }

    bool operator == (const GenomePosition &other) const
    {
        return referenceId == other.referenceId &&
                referenceName == other.referenceName &&
                position == other.position;
    }

    GenomePosition& operator += (int x)
    {
        position += x;
        return *this;
    }

    GenomePosition& operator -= (int x)
    {
        *this += -x;
        return *this;
    }

    friend std::ostream &operator <<(std::ostream& stream, const GenomePosition& gPos);

private:
    int referenceId;
    std::string referenceName;
    int position;
};

const GenomePosition operator + (const GenomePosition& one, int x);

const GenomePosition operator - (const GenomePosition& one, int x);

#endif // GENOMEPOSITION_H
