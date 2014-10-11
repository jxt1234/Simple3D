#include "test/GLTest.h"
#include "core/GLBmp.h"
#include "GL/GLBitmapWork.h"

class GLBitmapWorkTest:public GLTest
{
    public:
        virtual void run();
        GLBitmapWorkTest(){}
        virtual ~GLBitmapWorkTest(){}
};

void GLBitmapWorkTest::run()
{
    GPPtr<GLBmp> src = new GLBmp("input2.jpg");
    GPPtr<GLBmp> dst = new GLBmp(1024, 720);
    {
        GPPtr<GLTextureWork> _w= new GLTextureWork(NULL, NULL);
        GPPtr<GLBitmapWork> w = new GLBitmapWork(_w);
        w->set(src, dst);
        w->runOnePass();
    }
    dst->save("output/GLBitmapWorkTest.png");
}
static GLTestRegister<GLBitmapWorkTest> a("GLBitmapWorkTest");
