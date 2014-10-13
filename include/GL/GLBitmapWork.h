#ifndef GL_GLBITMAPWORK_H
#define GL_GLBITMAPWORK_H
#include "head.h"
#include "GLWork.h"
#include "GLProgram.h"
#include "GLTexture.h"
#include "GLTextureWork.h"
#include "core/GLBmp.h"
#include "utils/GLLock.h"
/*This kind of work run glsl from src to dst, if dst is NULL, then it write result to src*/
class GLBitmapWork:public GLWork
{
    public:
        GLBitmapWork(GPPtr<GLTextureWork> work, bool filter = true);
        virtual ~GLBitmapWork();
        void set(GPPtr<GLBmp> src, GPPtr<GLBmp> dst);
        //Must in GL Thread
        virtual bool onPrepare();
        virtual void onProcess();
        virtual void onFinish();
        virtual void onDestroy();

        void GetShader(std::ostream& vert, std::ostream& frag) const;
        inline void use(int id, int w, int h) const {mWork->onUse(id, w, h);}

        inline GPPtr<GLTextureWork> work() const{return mWork;}

    private:
        GPPtr<GLBmp> mSrc;
        GPPtr<GLBmp> mDst;
        GPPtr<GLTexture> mSrcT;
        GPPtr<GLTexture> mDstT;

        GPPtr<GLTextureWork> mWork;
        bool mFilter;

        GLLock mLock;
};
#endif
