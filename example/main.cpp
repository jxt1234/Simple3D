#include "test/GLTest.h"
#include "GL/GLBitmapWorkFactory.h"
#include "GL/GLContext.h"
#include <sstream>
int main()
{
    GLContext::init();
    GPPtr<GLBmp> src = new GLBmp("input2.jpg");
    int w = src->width();
    int h = src->height();
    int i = 4;
    {
        GPPtr<GLBmp> dst = new GLBmp(w*i, h*i);
        GPPtr<GLBitmapWork> w = GLBitmapWorkFactory::create("Bicubic");
        w->set(src, dst);
        w->runOnePass();
        std::ostringstream fileName;
        fileName << "output/ScaleExample.png";
        dst->save(fileName.str().c_str());
    }
    GLContext::destroy();
    return 1;
}
