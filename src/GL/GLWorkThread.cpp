#include "GL/GLWorkThread.h"
GLWorkThread::GLWorkThread():GLThread(false)
{
    mContext = NULL;
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
    mWait4Work.wait();
    WORK w;
    GLAutoLock _l(mWorkLock);
    while (!mWorks.empty())
    {
        w = mWorks.front();
        mWorks.pop();
        (w.first)->runOnePass();
        Sema* s = (Sema*)(w.second.get());
        s->post();
    }
    return true;
}

void GLWorkThread::destroy()
{
    GLContext::destroy(mContext);
}
void GLWorkThread::readyToRun()
{
    mContext = GLContext::init();
}
