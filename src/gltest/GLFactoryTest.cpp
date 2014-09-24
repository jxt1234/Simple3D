#include "test/GLTest.h"
#include "GL/GLBitmapWorkFactory.h"
#include <iostream>

class GLFactoryTest:public GLTest
{
    public:
        virtual void run();
        GLFactoryTest(){}
        virtual ~GLFactoryTest(){}
};

void GLFactoryTest::run()
{
    GLBitmapWorkFactory::printMethods(std::cout);

    GPPtr<GLBmp> src = new GLBmp("input.jpg");
    GPPtr<GLBmp> dst = new GLBmp(src->width(), src->height());
    GPPtr<GLBitmapWork> work = GLBitmapWorkFactory::create("Filter");
    work->set(src, dst);
    work->runOnePass();
    dst->save("output/Filter.png");
}
static GLTestRegister<GLFactoryTest> a("GLFactoryTest");
