#include "test/GLTest.h"
#include "utils/debug.h"
#include "utils/GLOnceWork.h"
#include <stdlib.h>
#include <vector>

class GLOnceWorkTest:public GLTest
{
    public:
        virtual void run();
        GLOnceWorkTest(){}
        virtual ~GLOnceWorkTest(){}
};

void GLOnceWorkTest::run()
{
    int u = 0;
    std::function<void(void)> f = [&](){
        FUNC_PRINT(u);
        u++;
    };
    std::vector<GPPtr<GLOnceWork> > works;
    for (int i=0; i<10; ++i)
    {
        GPPtr<GLOnceWork> w = new GLOnceWork(f);
        w->start();
        works.push_back(w);
    }
    for (auto w : works)
    {
        w->stop();
    }
    works.clear();
}
static GLTestRegister<GLOnceWorkTest> a("GLOnceWorkTest");
