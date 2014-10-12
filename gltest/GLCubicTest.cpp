#include "test/GLTest.h"
#include "GL/GLBitmapWorkFactory.h"
#include <sstream>

class GLCubicTest:public GLTest
{
    public:
        virtual void run();
        GLCubicTest(){}
        virtual ~GLCubicTest(){}
};

void GLCubicTest::run()
{
    GPPtr<GLBmp> src = new GLBmp("input2.jpg");
    int w = src->width();
    int h = src->height();
    int i = 4;
    {
        GPPtr<GLBmp> dst = new GLBmp(w*i, h*i);
        GPPtr<GLBitmapWork> w = GLBitmapWorkFactory::create("Bicubic");
        w->set(src, dst);
        w->runOnePass();
        std::ostringstream fileName;
        fileName << "output/GLCubicTest.png";
        dst->save(fileName.str().c_str());
    }
}
static GLTestRegister<GLCubicTest> a("GLCubicTest");
