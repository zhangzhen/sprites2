#include "AGEAlignerAdapter.h"
#include "age/AGEaligner.hh"
#include "error.h"
#include "DoubleFragsAlnResult.h"


IAlignmentResult *AGEAlignerAdapter::Align(const std::string &v, const std::string &w, const ScoreParam &sParam)
{

    int flag = AGEaligner::INDEL_FLAG;


    Scorer scr(sParam.GetMatch(), sParam.GetMismatch(), sParam.GetGapStart(), sParam.GetGap());

    Sequence seq1(v.c_str());
    Sequence seq2(w.c_str());

    AGEaligner aligner(seq1, seq2);

    if(!aligner.align(scr,flag)) error("AGE alignment error");

    AliFragment *f = aligner.GetAliFragments();

    AlignmentFragment aFragment1(f->ali1(),
                                 f->ali2(),
                                 Interval(f->start1() - 1, f->end1() - 1),
                                 Interval(f->start2() - 1, f->end2() - 1));

    if (!(f=f->next())) return NULL;

    AlignmentFragment aFragment2(f->ali1(),
                                 f->ali2(),
                                 Interval(f->start1() - 1, f->end1() - 1),
                                 Interval(f->start2() - 1, f->end2() - 1));

    return new DoubleFragsAlnResult(v, w, aligner.score(), aFragment1, aFragment2);
}
