#include "core/GLBmp.h"
#include "utils/GLDebug.h"
#include <string>
#include <fstream>
#include <sstream>
#include "GL/GLBitmapWorkFactory.h"
#include <map>
#include "GL/GLContext.h"
#include "GL/GLBitmapWork.h"

using namespace std;

int main(int argc, char* argv[])
{
    GLASSERT(argc>=4);
    GLAutoContext __c;
    const char* inputfile = argv[1];
    const char* outputfile = argv[2];
    float scale = atof(argv[3]);
    GPPtr<GLBmp> src = new GLBmp(inputfile);
    printf("Origin Picture: %d X %d\n", src->width(), src->height());
    GPPtr<GLBmp> dst = new GLBmp(src->width()*scale, src->height()*scale);
    {
        GPPtr<GLBitmapWork> w = GLBitmapWorkFactory::create("Bicubic");
        w->set(src, dst);
        w->runOnePass();
    }
    dst->save(outputfile);
    return 1;
}
