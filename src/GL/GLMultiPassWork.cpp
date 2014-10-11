#include "GL/GLMultiPassWork.h"
#include <sstream>
typedef std::vector<GPPtr<GLProgram> >::iterator ITER;

GLMultiPassWork::GLMultiPassWork()
{
}
GLMultiPassWork::~GLMultiPassWork()
{
}

bool GLMultiPassWork::onPrepare()
{
    while(!this->vFinish())
    {
        std::ostringstream vertex, frag;
        this->onGenerateShader(vertex, frag);
        mShaders.push_back(new GLProgram(vertex.str(), frag.str()));
        this->vNext();
    }
    bool res = true;
    for (ITER i = mShaders.begin(); i!=mShaders.end(); i++)
    {
        res &= (*i)->init();
        if (!res)
        {
            FUNC_PRINT(res);
            return false;
        }
    }
    mTempBuffer = new GLTexture;
    mTempBuffer->upload(NULL, src_()->width(), src_()->height());
    return res;
}

/*FIXME Only the last time can we draw to the dst*/
void GLMultiPassWork::onProcess()
{
    int odd = mShaders.size()%2;
    GPPtr<GLTexture> current, next;
    GPPtr<GLTexture> src = src_();
    if (odd)
    {
        current = dst_();
        next = mTempBuffer;
    }
    else
    {
        current = mTempBuffer;
        next = dst_();
    }
    for (ITER i = mShaders.begin(); i!=mShaders.end(); i++)
    {
        setTexture(src, current);
        setProgram(*i);
        INHERIT::onProcess();
        /*Ping-Pong*/
        src = current;
        current = next;
        next = src;
    }
}

void GLMultiPassWork::addShader(GPPtr<GLProgram> s)
{
    mShaders.push_back(s);
}

void GLMultiPassWork::clearShaders()
{
    mShaders.clear();
}

void GLMultiPassWork::onDestroy()
{
    for (ITER i=mShaders.begin(); i!=mShaders.end(); i++)
    {
        (*i)->destroy();
    }
    INHERIT::onDestroy();
}
