#include "test/GLTest.h"
#include "transform/GLColorMap.h"
#include "utils/GLDebug.h"

class GLColorMapTest:public GLTest
{
    public:
        virtual void run();
        GLColorMapTest(){}
        virtual ~GLColorMapTest(){}
};

void GLColorMapTest::run()
{
    GPPtr<GLBmp> src = new GLBmp("input.jpg");
    GPPtr<GLBmp> colormap = new GLBmp(256, 1);
    for (int i=0; i<256; ++i)
    {
        auto c = colormap->getAddr(i, 0);
        c[0] = (i*i)%255;
        c[1] = i;
        c[2] = 255-i;
    }
    GLColorMapInner(src.get(), src.get(), colormap.get());
    src->save("output/GLColorMapTest.png");
}
static GLTestRegister<GLColorMapTest> a("GLColorMapTest");
