#include "GL/GLBitmapWork.h"
#include "GL/GLAutoFbo.h"
#include "GL/GLvboBuffer.h"
#include "GL/GLBitmapWorkFactory.h"
#include <sstream>

GLBitmapWork::GLBitmapWork(GPPtr<GLTextureWork> work, bool filter)
{
    mWork = work;
    mFilter = filter;
}
GLBitmapWork::~GLBitmapWork()
{
}

bool GLBitmapWork::onPrepare()
{
    GLASSERT(NULL!=mSrc.get() && NULL!=mDst.get());
    GLAutoLock _l(mLock);
    mSrcT = new GLTexture;
    mSrcT->setFilter(mFilter);
    mSrcT->upload(mSrc->pixels(), mSrc->width(), mSrc->height());
    mDstT = new GLTexture;
    mDstT->upload(NULL, mDst->width(), mDst->height());
    return mWork->onPrepare();;
}

void GLBitmapWork::onFinish()
{
    GLAutoLock _l(mLock);
    /*Read result back from texture*/
    assert(NULL!=mDst.get());
    if (NULL!=mDstT.get())
    {
        GLAutoFbo __f(*mDstT);
        mDstT->download(mDst->pixels());
    }
}

void GLBitmapWork::onProcess()
{
    std::vector<GLTexture*> source(1, mSrcT.get());
    mWork->run(mDstT.get(), source);
}

void GLBitmapWork::onDestroy()
{
    mDstT = NULL;
    mSrcT = NULL;
    mWork->onDestroy();
}

void GLBitmapWork::set(GPPtr<GLBmp> src, GPPtr<GLBmp> dst)
{
    mSrc = src;
    mDst = dst;
}

class GLBitmapWork_Creater:public GLBitmapWorkCreater
{
    public:
        virtual GLBitmapWork* vCreate(std::istream* input) const
        {
            GPPtr<GLTextureWork> work;
            if (NULL == input)
            {
                work = new GLTextureWork(NULL, NULL);
                return new GLBitmapWork(work);
            }
            std::istream& is = *input;
            std::ostringstream os;
            os << is.rdbuf();
            work = new GLTextureWork(NULL, os.str().c_str());
            return new GLBitmapWork(work);
        }
        virtual void vDetail(std::ostream& os) const
        {
            os <<"Usage: input stream was the fragment shader, default shader is below:"<<std::endl;
        }
};

static GLBitmapWorkCreatorRegister<GLBitmapWork_Creater> __T("Basic");
