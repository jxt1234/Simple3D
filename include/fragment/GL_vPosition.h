#ifndef FRAGMENT_GL_VPOSITION_H
#define FRAGMENT_GL_VPOSITION_H

#include "GLAbstractRasterizatedVarying.h"
class GL_vPosition:public GLAbstractRasterizatedVarying
{
    public:
        GL_vPosition():GLAbstractRasterizatedVarying(3){}
        virtual ~GL_vPosition(){}
};

#endif
