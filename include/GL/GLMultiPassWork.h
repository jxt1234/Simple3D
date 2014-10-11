#ifndef GL_GLMULTIPASSWORK_H
#define GL_GLMULTIPASSWORK_H
#include "GLTextureWork.h"
class GLMultiPassWork:public GLTextureWork
{
    public:
        GLMultiPassWork();
        virtual ~GLMultiPassWork();
        virtual bool onPrepare();
        virtual void onProcess();
        virtual void onDestroy();
    private:
        /*FIXME delete this two api*/
        void addShader(GPPtr<GLProgram> program);
        void clearShaders();

        virtual bool vFinish() const {return true;}
        virtual void vNext() {}
        std::vector<GPPtr<GLProgram> > mShaders;
        GPPtr<GLTexture> mTempBuffer;
        typedef GLTextureWork INHERIT;
};
#endif
