#ifndef DISPLAY_GLOBJECT_H
#define DISPLAY_GLOBJECT_H
#include "utils/RefCount.h"
#include "math/GLMatrix4.h"
#include "head.h"

class CONTEXT_CLASS GLObject:public RefCount
{
    public:
        GLObject(){}
        virtual ~GLObject(){}
        virtual void onGenerateShader(std::ostream& vertex, std::ostream& frag) const {}
        virtual bool onPrepare() {return true;}
        virtual void onDraw(const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P) = 0;
};

class GLObjectCreator
{
    public:
        virtual CONTEXT_API GLObject* vCreate(std::istream* parameter=NULL) const = 0;
        virtual void vGetInfo(std::ostream& output) const = 0;

        GLObjectCreator(){}
        virtual ~GLObjectCreator(){}
};

class GLObjectIterator
{
    public:
        GLObjectIterator(){}
        virtual ~GLObjectIterator(){}
    protected:
        virtual GPPtr<GLObject> vCurrent() const = 0;
        virtual void vNext() = 0;
        virtual bool vEnd() const = 0;
        virtual void vRewind() = 0;
};
#endif
