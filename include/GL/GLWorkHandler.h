#include "GLWork.h"
class GLWorkSemore:public RefCount
{
    public:
        GLWorkSemore(){}
        virtual ~GLWorkSemore(){}

        virtual bool wait(int timeout_ms=0) = 0;
};
class GLWorkHandler
{
    public:
        virtual GPPtr<GLWorkSemore> queueWork(GPPtr<GLWork> work) = 0;
        GLWorkHandler(){}
        virtual ~GLWorkHandler(){}
};
