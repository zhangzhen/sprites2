#include "CallResult.h"

std::ostream& operator <<(std::ostream &stream, const CallResult &cResult)
{
    stream << cResult.cRegion << "\t"
              << cResult.startInterval << "\t"
              << cResult.endInterval << "\t"
              << cResult.microIns << "\t"
              << cResult.microHom;
    return stream;
}

