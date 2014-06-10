#ifndef VERTEX_GLVECTORVARYING_H
#define VERTEX_GLVECTORVARYING_H

#include "GLAbstractVarying.h"
#include "math/GLMatrix4.h"
#include "math/GLCurveSurface.h"

class GLVectorVarying:public GLAbstractVarying
{
    public:
        GLVectorVarying():GLAbstractVarying(4){}
        virtual ~GLVectorVarying(){}
        void addPoint(float x, float y, float z, float w);
        void normalize();
        void transform(const GLMatrix4& matrix);
    protected:
        float mBackup[4];
};

#endif
