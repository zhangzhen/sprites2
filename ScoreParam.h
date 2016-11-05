#ifndef SCOREPARAM_H
#define SCOREPARAM_H

class ScoreParam
{
public:
    ScoreParam(int match, int mismatch, int gap, int gapStart=0)
        : match(match),
          mismatch(mismatch),
          gap(gap),
          gapStart(gapStart)
    {}

    int MatchChar(char a, char b) const
    {
        if (a == b) return match;
        return mismatch;
    }

    int GetGap() const { return gap; }

    int GetMatch() const {return match; }

    int GetMismatch() const { return mismatch; }

    int GetGapStart() const { return gapStart; }

private:
    int match;
    int mismatch;
    int gap;
    int gapStart;
};

#endif // SCOREPARAM_H
