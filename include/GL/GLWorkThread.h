#ifndef GL_GLWORKTHREAD_H
#define GL_GLWORKTHREAD_H
#include <queue>
#include "utils/GLThread.h"
#include "GLWorkHandler.h"
#include "GLContext.h"
class GLWorkThread:public GLThread, GLWorkHandler
{
    public:
        class Sema:public GLWorkSemore
        {
            public:
                virtual bool wait(int timeout_ms)
                {
                    mSem.wait();
                    return true;
                }
                void post()
                {
                    mSem.post();
                }
            private:
                GLSema mSem;
        };
        virtual GPPtr<GLWorkSemore> queueWork(GPPtr<GLWork> work);
        GLWorkThread();
        virtual ~GLWorkThread();
    protected:
        virtual void onStart();
        virtual void onStop();
        virtual void readyToRun();
        virtual bool threadLoop();
        virtual void destroy();
    private:
        typedef std::pair<GPPtr<GLWork>, GPPtr<GLWorkSemore> >WORK;
        std::queue<WORK> mWorks;
        GLSema mWait4Work;
        GLLock mWorkLock;
        GLContext::nativeContext* mContext;
};
#endif
