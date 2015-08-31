#include "test/GLTest.h"
#include "transform/GLBasicTransform.h"
#include "core/GLBmp.h"

class GLRotateTest:public GLTest
{
    public:
        virtual void run()
        {
            GLBmp src("ori.png");
            GLBmp b(src.width(), src.height());
            GLRotate(src, b, 120);
            b.save("output/rotate.png");
            GLBmp c(src.height(), src.width());
            GLRotate(src, c, 90, false);
            c.save("output/rotate_noscale.png");
        }
        GLRotateTest(){}
        virtual ~GLRotateTest(){}
};

static GLTestRegister<GLRotateTest> a("rotate_Test");
