#ifndef DISPLAY_GLOBJECT_H
#define DISPLAY_GLOBJECT_H
#include "utils/RefCount.h"
#include "math/GLMatrix4.h"
#include "head.h"
#include <string>

class CONTEXT_CLASS GLObject:public RefCount
{
    public:
        GLObject(){}
        virtual ~GLObject(){}
        /*Can be called before onPrepare*/
        virtual bool onGenerateShader(std::ostream& vertex, std::ostream& frag) const {return false;}
        virtual bool onPrepare() {return true;}

        /*Must be called after onPrepare*/
        /*After onPrepare, return the self program id, if it has no program, return 0*/
        virtual int vGetProgramId() const {return 0;}
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

class GLAutoDrawObject
{
    public:
        GLAutoDrawObject(GPPtr<GLObject> obj, const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P):mM(M), mV(V), mP(P){mObj = obj;}
        ~GLAutoDrawObject(){mObj->onDraw(mM, mV, mP);}
    private:
        GPPtr<GLObject> mObj;
        const GLMatrix4& mM;
        const GLMatrix4& mV;
        const GLMatrix4& mP;
};
#endif
