#ifndef MATH_GLSPHERE_H
#define MATH_GLSPHERE_H
#include "GLCurveSurface.h"
#include "GLVector.h"

class GLSphere:public GLCurveSurface
{
    public:
        GLSphere(float _r, float x=0, float y=0, float z=0)
        {
            r=_r;
            m[0] = x;
            m[1] = y;
            m[2] = z;
        }
        virtual void pos(float* out, float u, float v);
        virtual void normal(float* out, float u, float v);
        virtual ~GLSphere(){}
    protected:
        GLVector::vec3 m;
        float r;
};



#endif
