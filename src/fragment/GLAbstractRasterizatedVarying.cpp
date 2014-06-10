#include "fragment/GLAbstractRasterizatedVarying.h"
#include <sstream>

std::string GLAbstractRasterizatedVarying::print()
{
    std::ostringstream os;
    os <<"\n";
    for (int i=0; i<mData.size(); ++i)
    {
        float* data = mData[i];
        for (int j=0; j<mUnit; ++j)
        {
            os << data[j]<<" ";
        }
        os << "\n";
    }
    return os.str();
}
