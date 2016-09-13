#include "vertex/GLAbstractVarying.h"

#include "utils/GLDebug.h"

void GLAbstractVarying::print()
{
    for (int i=0; i<mData.size(); ++i)
    {
        float* p = mData[i];
        for (int j=0; j<mUnit; ++j)
        {
            printf("%f ", p[j]);
        }
        printf("\n");
    }
}
