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
    GLBmp src("input.jpg");
    GLBmp dst(1024, 720);
    {
        GLBitmapWork* w = new GLBitmapWork(&src, &dst);
        w->onPrepare();
        w->onProcess();
        w->onFinish();
        
        w->decRef();
    }
    dst.save("output/GLBitmapWorkTest.png");
}
static GLTestRegister<GLBitmapWorkTest> a("GLBitmapWorkTest");
