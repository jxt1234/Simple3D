#include "test/GLTest.h"
#include "GL/GLFilterWork.h"

class GLFilterTest:public GLTest
{
    public:
        virtual void run();
        GLFilterTest(){}
        virtual ~GLFilterTest(){}
};

void GLFilterTest::run()
{
    GLBmp src("input2.jpg");
    GLBmp dst(1024, 720);
    {
        GLBitmapWork* w = new GLFilterWork(&src, &dst);
        w->runOnePass();
        
        w->decRef();
    }
    dst.save("output/GLFilterTest.png");
}
static GLTestRegister<GLFilterTest> a("GLFilterTest");
