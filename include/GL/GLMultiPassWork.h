#ifndef GL_GLMULTIPASSWORK_H
#define GL_GLMULTIPASSWORK_H
#include "GLBitmapWork.h"
class GLMultiPassWork:public GLBitmapWork
{
    public:
        GLMultiPassWork(GLBmp* src, GLBmp* dst);
        virtual ~GLMultiPassWork();
        void addShader(GPPtr<Shader> s);
        virtual bool onPrepare();
        virtual void onProcess();
        virtual void onDestroy();
    private:
        std::vector<GPPtr<Shader> > mShaders;
        GPPtr<GLTexture> mTempBuffer;
        typedef GLBitmapWork INHERIT;
};
#endif
