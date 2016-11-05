#ifndef CALLPARAMS
#define CALLPARAMS

class CallParams
{
public:
    CallParams(int minClip, double maxErrorRate)
        : minClip(minClip), maxErrorRate(maxErrorRate)
    {}

    int GetMinClip() const
    {
        return minClip;
    }

    double GetMaxErrorRate() const
    {
        return maxErrorRate;
    }

private:
    int minClip;
    double maxErrorRate;
};

#endif // CALLPARAMS

