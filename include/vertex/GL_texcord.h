#ifndef VERTEX_GL_TEXCORD_H
#define VERTEX_GL_TEXCORD_H
#include "interface/IVarying.h"
#include "GLAbstractVarying.h"
class GL_texcord:public GLAbstractVarying
{
    public:
        //For Rasterization
        GL_texcord():GLAbstractVarying(2){}
        void addPoint(float u, float v)
        {
            float* r=alloc();
            r[0] = u;
            r[1] = v;
        }
        virtual ~GL_texcord(){}
    protected:
};


#endif
