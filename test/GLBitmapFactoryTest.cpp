#include "test/GLTest.h"
#include "core/GLBitmapFactory.h"

class GLBitmapFactoryTest:public GLTest
{
    public:
        virtual void run();
        GLBitmapFactoryTest(){}
        virtual ~GLBitmapFactoryTest(){}
};

void GLBitmapFactoryTest::run()
{
    GPPtr<GLBmp> b = GLBitmapFactory::create("input.jpg");
    GLBitmapFactory::dump(b.get(), "output/GLBitmapFactoryTest.png");
}
static GLTestRegister<GLBitmapFactoryTest> a("GLBitmapFactoryTest");
