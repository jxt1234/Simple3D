#include "vertex/GL_Normal.h"
#include "math/GLVector.h"
#include <assert.h>

#define VECTOR_NUM 3

using namespace GLVector;

GL_Normal::GL_Normal(IVarying& pos):GLAbstractVarying(3)
{
    assert(pos.unit()>=VECTOR_NUM);
    assert(pos.size()%VECTOR_NUM == 0);
    int size = pos.size();
    vec3 v1;
    vec3 v2;
    vec3 out;
    for (int i=0; i<size; i+=VECTOR_NUM)
    {
        float* p1 = pos.load(i);
        float* p2 = pos.load(i+1);
        float* p3 = pos.load(i+2);
        minus(v1, p1, p2, VECTOR_NUM);
        minus(v2, p1, p3, VECTOR_NUM);
        cross(out, v1, v2);
        normalize(out);
        for (int j=0;j<VECTOR_NUM;++j)
        {
            addPoint(out[0], out[1], out[2]);
        }
    }
}
