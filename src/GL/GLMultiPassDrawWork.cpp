#include "GL/GLMultiPassDrawWork.h"
#include "GL/GLAutoFbo.h"
#include "GL/GLvboBufferManager.h"

GLMultiPassDrawWork::GLMultiPassDrawWork(const std::vector<GPPtr<IGLDrawWork> >& works)
{
    GLASSERT(1<=works.size());
    mWorks = works;
    mFirstTexture = new GLTexture;
    mSecondTexture = new GLTexture;
    mVs = GLvboBufferManager::createBasicPos();
    mTs = GLvboBufferManager::createBasicTex();
    
    mOffset.push_back(0);
    for (int i=1; i<mWorks.size(); ++i)
    {
        mOffset.push_back(mOffset[i-1] + mWorks[i-1]->vMap(NULL, 0));
    }
}
GLMultiPassDrawWork::~GLMultiPassDrawWork()
{
    
}
void GLMultiPassDrawWork::onDraw(GLTexture** src__, int num, GLvboBuffer* vs, GLvboBuffer* ts)
{
    GLASSERT(NULL!=vs);
    GLASSERT(NULL!=ts);
    GLASSERT(NULL!=src__);
    GLASSERT(1 == num);
    GLASSERT(NULL!=src__[0]);
    auto w = src__[0]->width();
    auto h = src__[0]->height();
    auto lastWork = mWorks[mWorks.size()-1];
    if (mWorks.size()<=1)
    {
        lastWork->onDraw(src__, 1, vs, ts);
        return;
    }
    GPPtr<GLTexture> dst = mSecondTexture;
    GPPtr<GLTexture> src = mFirstTexture;
    /*First Pass, use texture srcid*/
    if (src->width()!=w || src->height()!=h)
    {
        src->upload(NULL, w, h);
    }
    {
        GLAutoFbo __fbo(*src);
        mWorks[0]->onDraw(src__, num, mVs.get(), mTs.get());
    }
    GPPtr<GLTexture> temp;
    /*Mid passes, pingpong*/
    for (int i=1; i<mWorks.size()-1; ++i)
    {
        if (dst->width()!=w || dst->height()!=h)
        {
            dst->upload(NULL, w, h);
        }
        {
            GLAutoFbo __fbo(*dst);
            GLTexture* ssrc = src.get();
            mWorks[i]->onDraw(&ssrc, 1, mVs.get(), mTs.get());
        }
        temp = dst;
        dst = src;
        src = temp;
    }
    /*Last Pass, use the dst texture to draw*/
    GLTexture* ssrc = src.get();
    lastWork->onDraw(&ssrc, 1, vs, ts);
}
size_t GLMultiPassDrawWork::vMap(double* parameters, size_t n)
{
    GLASSERT(mOffset.size() == mWorks.size()+1);
    if (NULL == parameters)
    {
        return mOffset[mOffset.size()-1];
    }
    for (int i=0; i<mWorks.size(); ++i)
    {
        mWorks[i]->vMap(parameters+mOffset[i], mOffset[i+1]-mOffset[i]);
    }
    GLASSERT(n == mOffset[mOffset.size()-1]);
    return mOffset[mOffset.size()-1];
}
