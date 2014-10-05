#include "test/GLTest.h"
#include "core/GLBmp.h"

class GLBmpTest:public GLTest
{
    public:
        virtual void run()
        {
            GLBmp b(720,1280);
            GLColor c;
            c.r = 100;c.g = 255; c.b=255;c.a=100;
            b.clear(c);
            b.save("output/dst.png");
            GLBmp ori("ori.png");
            ori.save("output/ori.png");
        }
        GLBmpTest(){}
        virtual ~GLBmpTest(){}
};

static GLTestRegister<GLBmpTest> a("bmpTest");
