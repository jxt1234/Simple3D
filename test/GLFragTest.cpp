#include "test/GLTest.h"
#include "core/GLBmp.h"
#include "transform/GLFragPicture.h"

class GLFragTest:public GLTest
{
    public:
        virtual void run()
        {
            GLBmp b(720,1280);
            GLGenFragPicNewTon(b);
            b.save("output/frag.png");
        }
        GLFragTest(){}
        virtual ~GLFragTest(){}
};

static GLTestRegister<GLFragTest> a("fragTest");
