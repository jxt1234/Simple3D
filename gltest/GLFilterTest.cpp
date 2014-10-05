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
        const float p[] = {0.1,0.2,0.4,0.2,0.1};
        int n = sizeof(p)/sizeof(float);
        GLBitmapWork* w = new GLFilterWork(&src, &dst, p, n);
        w->runOnePass();
        
        w->decRef();
    }
    dst.save("output/GLFilterTest.png");
}
static GLTestRegister<GLFilterTest> a("GLFilterTest");
