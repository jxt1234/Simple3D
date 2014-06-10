#ifndef FRAGMENT_GL_FRAGPOSITION_H
#define FRAGMENT_GL_FRAGPOSITION_H

#include "GLAbstractRasterizatedVarying.h"
class GL_FragPosition:public GLAbstractRasterizatedVarying
{
    public:
        //Basic
        GL_FragPosition():GLAbstractRasterizatedVarying(2){}
        virtual ~GL_FragPosition(){}
};

#endif
