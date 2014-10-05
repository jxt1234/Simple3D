#include "test/GLTest.h"
#include "GL/GLBitmapWorkFactory.h"
#include <iostream>
#include <assert.h>

class GLFractionByGLTest:public GLTest
{
    public:
        virtual void run();
        GLFractionByGLTest(){}
        virtual ~GLFractionByGLTest(){}
};

void GLFractionByGLTest::run()
{
    GPPtr<GLBmp> dst = new GLBmp(720,1280);
    GPPtr<GLBitmapWork> work = GLBitmapWorkFactory::create("Fraction");
    assert(NULL!=work.get());
    work->set(dst, dst);
    {
        int start = clock();
        work->runOnePass();
        int end = clock();
        FUNC_PRINT(end-start);
    }
    dst->save("output/Fraction.png");
}
static GLTestRegister<GLFractionByGLTest> a("GLFractionByGLTest");
