#ifndef ALIGNMENTRESULT2
#define ALIGNMENTRESULT2

#include <string>

class IAlignmentResult
{
public:
    IAlignmentResult(const std::string& v, const std::string& w, int score)
        : v(v),
          w(w),
          score(score)
    {}

    virtual ~IAlignmentResult() {}

    std::string GetV() const { return v; }

    std::string GetW() const { return w; }

    int GetScore() const { return score; }

    virtual void PrintAlignment()  = 0;

    virtual double GetPercentIdentity() = 0;

    virtual void Flip() = 0;

protected:
    std::string v;
    std::string w;
    int score;
};

#endif // ALIGNMENTRESULT2

