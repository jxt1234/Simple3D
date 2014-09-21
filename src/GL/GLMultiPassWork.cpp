#include "GL/GLMultiPassWork.h"
typedef std::vector<GPPtr<GLBitmapWork::Shader> >::iterator ITER;

GLMultiPassWork::GLMultiPassWork(GLBmp* src, GLBmp* dst):GLBitmapWork(src, dst)
{
}
GLMultiPassWork::~GLMultiPassWork()
{
}

bool GLMultiPassWork::onPrepare()
{
    bool res = true;
    for (ITER i = mShaders.begin(); i!=mShaders.end(); i++)
    {
        res &= (*i)->setUp();
    }
    res &= INHERIT::onPrepare();
    mTempBuffer = new GLTexture;
    mTempBuffer->upload(NULL, mSrcT->width(), mSrcT->height());
    return res;
}

/*FIXME Only the last time can we draw to the dst*/
void GLMultiPassWork::onProcess()
{
    int odd = mShaders.size()%2;
    GPPtr<GLTexture> current, next;
    if (odd)
    {
        current = mDstT;
        next = mTempBuffer;
    }
    else
    {
        current = mTempBuffer;
        next = mDstT;
    }
    for (ITER i = mShaders.begin(); i!=mShaders.end(); i++)
    {
        mDstT = current;
        mShader = *i;
        INHERIT::onProcess();
        /*Ping-Pong*/
        mSrcT = current;
        current = next;
        next = mSrcT;
    }
}

void GLMultiPassWork::addShader(GPPtr<GLBitmapWork::Shader> s)
{
    mShaders.push_back(s);
}

void GLMultiPassWork::onDestroy()
{
    mShaders.clear();
    INHERIT::onDestroy();
}
