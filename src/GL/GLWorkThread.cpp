#include "GL/GLWorkThread.h"
GLWorkThread::GLWorkThread(func create, func dest)
{
    mInit = create;
    mDestroy = dest;
}
GLWorkThread::~GLWorkThread()
{
}

void GLWorkThread::onStop()
{
    mWait4Work.post();
}

void GLWorkThread::onStart()
{
}

GPPtr<GLWorkSemore> GLWorkThread::queueWork(GPPtr<GLWork> work)
{
    GPPtr<GLWorkSemore> s = new Sema;
    GLAutoLock _l(mWorkLock);
    mWorks.push(std::make_pair(work, s));
    mWait4Work.post();
    return s;
}

bool GLWorkThread::threadLoop()
{
    if (mWorks.empty())
    {
        mWait4Work.wait();
    }
    WORK w;
    {
        GLAutoLock _l(mWorkLock);
        w = mWorks.front();
        mWorks.pop();
    }
    (w.first)->runOnePass();
    Sema* s = (Sema*)(w.second.get());
    s->post();
    return true;
}

void GLWorkThread::destroy()
{
    if (NULL!=mDestroy)
    {
        mDestroy();
    }
}
void GLWorkThread::readyToRun()
{
    if (NULL!=mInit)
    {
        mInit();
    }
}
