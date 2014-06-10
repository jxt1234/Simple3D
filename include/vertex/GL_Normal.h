#ifndef VERTEX_GL_NORMAL_H
#define VERTEX_GL_NORMAL_H
#include "GLAbstractVarying.h"

class GL_Normal:public GLAbstractVarying
{
    public:
        GL_Normal():GLAbstractVarying(3){}
        GL_Normal(IVarying& pos);
        void addPoint(float x, float y, float z)
        {
            float* p = alloc();
            p[0] = x;
            p[1] = y;
            p[2] = z;
        }
        virtual ~GL_Normal(){}
};


#endif
