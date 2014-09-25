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
    GPPtr<GLBmp> dst = new GLBmp(1280, 720);
    GPPtr<GLBitmapWork> work = GLBitmapWorkFactory::create("Fraction");
    assert(NULL!=work.get());
    work->set(dst, dst);
    work->runOnePass();
    dst->save("output/Fraction.png");
}
static GLTestRegister<GLFractionByGLTest> a("GLFractionByGLTest");
