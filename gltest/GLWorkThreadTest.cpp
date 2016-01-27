#include "test/GLTest.h"
#include "core/GLBmp.h"
#include "GL/GLBitmapWorkFactory.h"
#include "GL/GLBitmapWork.h"
#include "GL/GLWorkThread.h"
#include "GL/GLContext.h"

class GLWorkThreadTest:public GLTest
{
    public:
        virtual void run();
        GLWorkThreadTest(){}
        virtual ~GLWorkThreadTest(){}
};

void GLWorkThreadTest::run()
{
    GLWorkThread worker;
    worker.start();
    GPPtr<GLBmp> src = new GLBmp("input2.jpg");
    GPPtr<GLBmp> dst = new GLBmp(720,1280);
    GLBitmapWork* work = GLBitmapWorkFactory::create("Bicubic");
    assert(NULL!=work);
    GPPtr<GLWork> w = work;

    work->set(src, dst);
    GPPtr<GLWorkSemore> s = worker.queueWork(w);
    s->wait();
    dst->save("output/GLWorkThreadTest.png");
    worker.stop();
}
static GLTestRegister<GLWorkThreadTest> a("GLWorkThreadTest");
