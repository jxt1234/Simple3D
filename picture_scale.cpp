#include "core/GLBmp.h"
#include "utils/debug.h"
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
    const char* outputfile = argv[1];
    int dstW = atoi(argv[2]);
    int dstH = atoi(argv[3]);
    GPPtr<GLBmp> src = new GLBmp(inputfile);
    GPPtr<GLBmp> dst = new GLBmp(dstW, dstH);
    {
        GPPtr<GLBitmapWork> w = GLBitmapWorkFactory::create("Bicubic");
        w->set(src, dst);
        w->runOnePass();
    }
    dst->save(outputfile);
    return 1;
}
