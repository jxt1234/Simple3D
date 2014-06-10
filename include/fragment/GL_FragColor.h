#ifndef FRAGMENT_GL_FRAGCOLOR_H
#define FRAGMENT_GL_FRAGCOLOR_H

#include "GLAbstractRasterizatedVarying.h"
class GL_FragColor:public GLAbstractRasterizatedVarying
{
    public:
        GL_FragColor():GLAbstractRasterizatedVarying(4){}
        virtual ~GL_FragColor(){}
};

#endif
