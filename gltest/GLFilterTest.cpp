#include "test/GLTest.h"
#include "GL/GLBitmapWork.h"
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
    GPPtr<GLBmp> src = new GLBmp("input2.jpg");
    GPPtr<GLBmp> dst = new GLBmp(1024, 720);
    {
        const float p[] = {0.1,0.2,0.4,0.2,0.1};
        int n = sizeof(p)/sizeof(float);
        GPPtr<GLTextureWork> _w = new GLFilterWork(p, n);
        GPPtr<GLBitmapWork> w = new GLBitmapWork(_w);
        w->set(src, dst);
        w->runOnePass();
    }
    dst->save("output/GLFilterTest.png");
}
static GLTestRegister<GLFilterTest> a("GLFilterTest");
