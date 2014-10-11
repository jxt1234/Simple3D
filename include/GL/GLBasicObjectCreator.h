#ifndef GL_GLBASICOBJECTCREATOR_H
#define GL_GLBASICOBJECTCREATOR_H
#include "GLObject.h"
class GLBasicObjectCreator:public GLObjectCreator
{
    public:
        virtual CONTEXT_API GLObject* vCreate(std::istream* parameter=NULL) const;
        virtual void vGetInfo(std::ostream& output) const;
};
#endif
