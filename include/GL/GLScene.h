#ifndef DISPLAY_GLSCENE_H
#define DISPLAY_GLSCENE_H
#include "GLObject.h"
#include "GLTransformer.h"

class GLScene:public GLObject, GLObjectIterator
{
    public:
        GLScene();
        GLScene(GPPtr<GLTransformer> t);
        inline GPPtr<GLTransformer> getTransformer(){return mTransformer;}
        virtual ~GLScene();
        virtual bool onPrepare();

        virtual const GLObjectCreator* vGetCreator() const = 0;

        virtual void vAddObject(GPPtr<GLObject> obj) = 0;
        virtual int size() const = 0;
        virtual void onDraw(const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P);
        virtual void vRemoveObject(GPPtr<GLObject> obj) = 0;
        virtual void vRemoveAll() = 0;
    private:
        GPPtr<GLTransformer> mTransformer;

};


#endif
