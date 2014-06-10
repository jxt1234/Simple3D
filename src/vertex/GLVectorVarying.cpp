#include "vertex/GLVectorVarying.h"
#include "math/GLVector.h"

void GLVectorVarying::normalize()
{
    for (int i=0; i<this->size(); ++i)
    {
        float* r = this->load(i);
        r[0] = r[0] / r[3];
        r[1] = r[1] / r[3];
        r[2] = r[2] / r[3];
        r[3] = r[3] / r[3];
    }
}


void GLVectorVarying::transform(const GLMatrix4& matrix)
{
    for (int i=0; i<this->size(); ++i)
    {
        float* r = this->load(i);
        matrix.transform(mBackup, r);
        r[0] = mBackup[0];
        r[1] = mBackup[1];
        r[2] = mBackup[2];
        r[3] = mBackup[3];
    }
}
void GLVectorVarying::addPoint(float x, float y, float z, float w)
{
    float* r = alloc();
    r[0] = x;
    r[1] = y;
    r[2] = z;
    r[3] = w;
}

