#include "GL/OpenGLWorker.h"
#include <stdlib.h>
#include "GL/GLContext.h"
#include "utils/GLDebug.h"
OpenGLWorker* OpenGLWorker::gInstance = NULL;

static GLLock gLock;


GLWorkThread* OpenGLWorker::getInstance()
{
    if (NULL == gInstance)
    {
        GLAutoLock _l(gLock);
        if (NULL == gInstance)
        {
            gInstance = new OpenGLWorker;
        }
    }
    GLASSERT(NULL!=gInstance);
    return gInstance->mThread;
}


OpenGLWorker::OpenGLWorker()
{
    mThread = new GLWorkThread();
    mThread->start();
}
OpenGLWorker::~OpenGLWorker()
{
    mThread->stop();
    delete mThread;
}
