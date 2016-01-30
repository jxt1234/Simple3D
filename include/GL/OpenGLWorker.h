#ifndef OPENGLWORKER_H
#define OPENGLWORKER_H
#include "GL/GLWorkThread.h"
class OpenGLWorker
{
public:
    static GLWorkThread* getInstance();
private:
    GLWorkThread* mThread;
    OpenGLWorker();
    ~OpenGLWorker();
    static OpenGLWorker* gInstance;
};
#endif
