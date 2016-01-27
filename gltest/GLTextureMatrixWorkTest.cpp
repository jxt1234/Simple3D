#include "test/GLTest.h"
#include "core/GLBmp.h"
#include "GL/GLBitmapWork.h"
#include "GL/GLTextureMatrixWork.h"

class GLTextureMatrixWorkTest:public GLTest
{
    public:
        virtual void run();
        GLTextureMatrixWorkTest(){}
        virtual ~GLTextureMatrixWorkTest(){}
};

void GLTextureMatrixWorkTest::run()
{
    GLMatrix4 current;
    GPPtr<GLBmp> src = new GLBmp("input2.jpg");
    GPPtr<GLBmp> dst = new GLBmp("input.jpg");
    current.setScale(0.1, 0.1, 0.1);
    {
        GPPtr<GLTextureWork> _w= new GLTextureMatrixWork(current);
        GPPtr<GLBitmapWork> w = new GLBitmapWork(_w);
        w->set(src, dst);
        w->runOnePass();
    }
    dst->save("output/GLTextureMatrixWorkTest.png");
}
static GLTestRegister<GLTextureMatrixWorkTest> a("GLTextureMatrixWorkTest");
