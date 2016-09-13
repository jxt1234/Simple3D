#include "core/GLBmp.h"
#include "utils/GLDebug.h"
#include <fstream>
#include <sstream>

int test_main(const char* input, const char* target)
{
    GPPtr<GLBmp> src = new GLBmp(input);
    GLASSERT(NULL!=src.get());
    std::ofstream output(target);
    auto w = src->width();
    auto h = src->height();
    for (int y=0; y<h; ++y)
    {
        for (int x=0; x<w; ++x)
        {
            auto _src = src->getAddr(x, y);
            output << _src[0] << " "<<_src[1] << " "<<_src[2]<<" "<<_src[3] << "\n";
        }
    }
    return 1;
}
int main(int argc, char* argv[])
{
    GLASSERT(argc>=3);
    return test_main(argv[1],argv[2]);
}
