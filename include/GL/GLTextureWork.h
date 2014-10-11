#ifndef GL_GLTEXTUREWORK_H
#define GL_GLTEXTUREWORK_H
#include "head.h"
#include "GLWork.h"
#include "GLProgram.h"
#include "GLTexture.h"
#include "GLvboBuffer.h"
class GLTextureWork:public GLWork
{
    public:
        GLTextureWork();
        GLTextureWork(const char* vertex, const char* frag);
        virtual ~GLTextureWork();
        //Must in GL Thread
        virtual bool onPrepare();
        virtual void onProcess();
        virtual void onFinish();
        virtual void onDestroy();
        virtual void onUse(int proId, int srcW, int srcH) {}
        virtual bool onGenerateShader(std::ostream& vertex, std::ostream& frag) const {return false;}
        void setTexture(GPPtr<GLTexture> src, GPPtr<GLTexture> dst);
        void setProgram(GPPtr<GLProgram> pro) {mShader = pro;}
        void DefaultVertex(std::ostream& vertex) const;
    protected:
        inline GPPtr<GLTexture> src_() const {return mSrcT;}
        inline GPPtr<GLTexture> dst_() const {return mDstT;}
    private:
        GPPtr<GLTexture> mSrcT;
        GPPtr<GLTexture> mDstT;
        GPPtr<GLProgram> mShader;
};
#endif
