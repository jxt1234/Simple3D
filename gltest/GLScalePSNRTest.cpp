#include "test/GLTest.h"
#include "GL/GLBitmapWorkFactory.h"
#include <sstream>

class GLScalePSNRTest:public GLTest
{
    public:
        virtual void run();
        GLScalePSNRTest(){}
        virtual ~GLScalePSNRTest(){}
};

void GLScalePSNRTest::run()
{
    const int scale = 5;
    GPPtr<GLBmp> origin = new GLBmp("input2.jpg");
    int w = origin->width();
    int h = origin->height();
    GPPtr<GLBmp> src = new GLBmp(w/scale, h/scale);
    GPPtr<GLBmp> dst1 = new GLBmp(w, h);
    GPPtr<GLBmp> dst2 = new GLBmp(w, h);
    //reduce
    {
        GPPtr<GLBitmapWork> w = GLBitmapWorkFactory::create("Basic");
        w->set(origin, src);
        w->runOnePass();
    }
    {
        GPPtr<GLBitmapWork> w = GLBitmapWorkFactory::create("Basic");
        w->set(src, dst1);
        w->runOnePass();
    }
    {
        GPPtr<GLBitmapWork> w = GLBitmapWorkFactory::create("Bicubic");
        w->set(src, dst2);
        w->runOnePass();
    }
    dst1->save("output/GLScalePSNRTest_bilinear.png");
    dst2->save("output/GLScalePSNRTest_bicubic.png");

    double p1 = origin->psnr(*dst1);
    double p2 = origin->psnr(*dst2);
    FUNC_PRINT_ALL(p1, f);
    FUNC_PRINT_ALL(p2, f);
}
static GLTestRegister<GLScalePSNRTest> a("GLScalePSNRTest");
