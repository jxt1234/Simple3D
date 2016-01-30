#include "GL/GLMultiBitmapWork.h"
#include "GL/GLAutoFbo.h"
void GLMultiBitmapWork::onProcess()
{
    GLASSERT(NULL!=mDst.get());
    GLASSERT(mWorks.size()>0);
    GPPtr<GLTexture> dstT = new GLTexture;
    dstT->upload(NULL, mDst->width(), mDst->height());
    for (auto w : mWorks)
    {
        GPPtr<GLTexture> src = new GLTexture;
        src->upload(w.second->pixels(), w.second->width(), w.second->height());
        std::vector<GLTexture*> srcs;
        srcs.push_back(src.get());
        w.first->onPrepare();
        w.first->run(dstT.get(), srcs);
    }
    {
        GLAutoFbo __f(*(dstT));
        dstT->download(mDst->pixels());
    }
}
GLMultiBitmapWork::GLMultiBitmapWork(GPPtr<GLBmp> dst)
{
    mDst = dst;
}
GLMultiBitmapWork::~GLMultiBitmapWork()
{
}
void GLMultiBitmapWork::addWork(GPPtr<GLTextureWork> work, GPPtr<GLBmp> src)
{
    mWorks.push_back(std::make_pair(work, src));
}
