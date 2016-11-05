#include "HTSlibSequenceFetcher.h"
#include "error.h"

#include <algorithm>

using namespace std;

HTSlibSequenceFetcher::HTSlibSequenceFetcher(const string& fastaFile)
{
    fai = fai_load(fastaFile.c_str());
    if (fai == NULL) error("Cannot load the indexed fasta.");
}

HTSlibSequenceFetcher::~HTSlibSequenceFetcher()
{
    if (fai != NULL) fai_destroy(fai);
}

ChromoFragment HTSlibSequenceFetcher::Fetch(const ChromosomeRegion &region)
{
    int len;
    char *s = faidx_fetch_seq(
                fai,
                (char *)region.GetReferenceName().c_str(),
                region.GetStartPosition() - 1,
                region.GetEndPosition() - 1,
                &len);
    if (s == NULL) error("cannot fetch the reference sequence");
    string str(s);
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return ChromoFragment(region.GetStart(), str);
}
