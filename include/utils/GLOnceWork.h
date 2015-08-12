#ifndef UTILS_GLONCEWORK_H
#define UTILS_GLONCEWORK_H
#include "GLThread.h"
#include <functional>
class GLOnceWork:public GLThread
{
    public:
        GLOnceWork(std::function<void(void)>& f):mF(f){}
        virtual ~GLOnceWork(){}
        virtual void readyToRun();
        virtual bool threadLoop();
        virtual void destroy();
    private:
        std::function<void(void)>& mF;
};
#endif
