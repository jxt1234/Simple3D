#ifndef UTILS_GLTHREAD_H
#define UTILS_GLTHREAD_H
#include "GLLock.h"
class GLThread
{
    public:
        GLThread(bool _start = true);
        virtual ~GLThread();
        void start();
        void stop();
    protected:
        /*Outside thread method */
        virtual void onStart(){}
        virtual void onStop(){}
        /*Inside thread method*/
        virtual void readyToRun() = 0;
        virtual bool threadLoop() = 0;
        virtual void destroy() = 0;
        void run();
        static void* threadFunc(void* arg);
    private:
        bool mRunning;
        void* mData;
        GLLock mLock;
};
class GLSema
{
    public:
        GLSema();
        ~GLSema();
        void wait();
        void post();
    private:
        void* mData;
};
#endif
