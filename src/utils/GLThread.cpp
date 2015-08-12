#include "utils/GLThread.h"
#include <semaphore.h>
#include <pthread.h>
#include <assert.h>

void* GLThread::threadFunc(void* arg)
{
    GLThread* t = (GLThread*)arg;
    t->run();
    return NULL;
}

GLThread::GLThread(bool _start)
{
    pthread_t* d = new pthread_t;
    mData = (void*)d;
    mRunning = false;
}
GLThread::~GLThread()
{
    stop();
    pthread_t* d = (pthread_t*)mData;
    delete d;
}

void GLThread::run()
{
    this->readyToRun();
    bool rerun = true;
    do
    {
        rerun = this->threadLoop();
    }while(mRunning && rerun);
    this->destroy();
}

void GLThread::start()
{
    GLAutoLock _l(mLock);
    if (!mRunning)
    {
        this->onStart();
        pthread_t* t = (pthread_t*)mData;
        pthread_create(t, NULL, GLThread::threadFunc, this);
        mRunning = true;
    }
}

void GLThread::stop()
{
    GLAutoLock _l(mLock);
    if (mRunning)
    {
        mRunning = false;
        this->onStop();
        pthread_t* t = (pthread_t*)mData;
        pthread_join(*t, NULL);
    }
}


GLSema::GLSema()
{
    sem_t* s = new sem_t;
    sem_init(s, 0, 0);
    mData = (void*)s;
}
GLSema::~GLSema()
{
    assert(NULL!=mData);
    sem_t* s = (sem_t*)(mData);
    sem_destroy(s);
    delete s;
}

void GLSema::wait()
{
    assert(NULL!=mData);
    sem_t* s = (sem_t*)(mData);
    sem_wait(s);
}

void GLSema::post()
{
    assert(NULL!=mData);
    sem_t* s = (sem_t*)(mData);
    sem_post(s);
}
