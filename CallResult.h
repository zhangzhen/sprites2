#ifndef CALLRESULT
#define CALLRESULT

#include "ChromosomeRegion.h"
#include "sequencefetcher.h"


class CallResult
{
public:
    CallResult(const ChromosomeRegion& cRegion,
               const Interval& startInterval,
               const Interval& endInterval,
               const std::string& microIns,
               const std::string& microHom)
        : cRegion(cRegion),
          startInterval(startInterval),
          endInterval(endInterval),
          microIns(microIns),
          microHom(microHom)
    {}

    ChromosomeRegion GetChromoRegion() const
    {
        return cRegion;
    }

    std::string GetMicroIns() const { return microIns; }

    std::string GetMicroHom() const { return microHom; }

    Interval GetStartInterval() const { return startInterval; }

    Interval GetEndInterval() const { return endInterval; }

    int GetStart1() const { return cRegion.GetStartPosition() + startInterval.GetStart(); }
    int GetEnd1() const { return cRegion.GetStartPosition() + startInterval.GetEnd(); }
    int GetStart2() const { return cRegion.GetEndPosition() + endInterval.GetStart(); }
    int GetEnd2() const { return cRegion.GetEndPosition() + endInterval.GetEnd(); }
	int GetSvLength() const { return cRegion.GetLength() - 2; }

	bool IsValid(int minSvLength)
	{
		return cRegion.GetLength() - 2 > abs(minSvLength);
	}

    friend std::ostream& operator <<(std::ostream& stream, const CallResult& cResult);

private:
    ChromosomeRegion cRegion;
    Interval startInterval;
    Interval endInterval;
    std::string microIns;
    std::string microHom;
};

#endif // CALLRESULT
