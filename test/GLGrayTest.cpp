#include "test/GLTest.h"
#include "core/GLBmp.h"
#include "core/GLGrayBitmap.h"

class GLGrayTest:public GLTest
{
    public:
        virtual void run();
        GLGrayTest(){}
        virtual ~GLGrayTest(){}
};

void GLGrayTest::run()
{
    GPPtr<GLBmp> origin = new GLBmp("input.jpg");
    GPPtr<GLGrayBitmap> gray = new GLGrayBitmap(origin->width(), origin->height());
    GLGrayBitmap::turnGray(gray.get(), origin.get());
    GLGrayBitmap::turnRGB(gray.get(), origin.get());
    origin->save("output/GLGrayBitmap.jpg");
}
static GLTestRegister<GLGrayTest> a("GLGrayTest");
