#include "GL/GLMultiPassDrawWork.h"
#include "GL/GLAutoFbo.h"

GLMultiPassDrawWork::GLMultiPassDrawWork(const std::vector<GPPtr<IGLDrawWork> >& works)
{
    GLASSERT(1<=works.size());
    mWorks = works;
    mFirstTexture = new GLTexture;
    mSecondTexture = new GLTexture;
    const float defaultVex[] = {
        -1.0, -1.0,
        -1.0, 1.0,
        1.0, -1.0,
        1.0, 1.0
    };
    mVs = new GLvboBuffer(defaultVex, 2, 4, GL_TRIANGLE_STRIP);
    const float defaultTex[] = {
        0.0,0.0,
        0.0,1.0,
        1.0,0.0,
        1.0,1.0
    };
    mTs = new GLvboBuffer(defaultTex, 2, 4, GL_TRIANGLE_STRIP);
    
    mOffset.push_back(0);
    for (int i=1; i<mWorks.size(); ++i)
    {
        mOffset.push_back(mOffset[i-1] + mWorks[i-1]->vMap(NULL, 0));
    }
}
GLMultiPassDrawWork::~GLMultiPassDrawWork()
{
    
}
void GLMultiPassDrawWork::onDraw(GLTexture* src__, GLvboBuffer* vs, GLvboBuffer* ts)
{
    GLASSERT(NULL!=vs);
    GLASSERT(NULL!=ts);
    GLASSERT(NULL!=src__);
    auto w = src__->width();
    auto h = src__->height();
    auto lastWork = mWorks[mWorks.size()-1];
    if (mWorks.size()<=1)
    {
        lastWork->onDraw(src__, vs, ts);
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
        mWorks[0]->onDraw(src__, mVs.get(), mTs.get());
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
            mWorks[i]->onDraw(src.get(), mVs.get(), mTs.get());
        }
        temp = dst;
        dst = src;
        src = temp;
    }
    /*Last Pass, use the dst texture to draw*/
    lastWork->onDraw(src.get(), vs, ts);
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
