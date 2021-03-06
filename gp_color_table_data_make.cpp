#include "core/GLBmp.h"
#include "utils/GLDebug.h"
#include <fstream>
#include <sstream>
#include <math.h>
//#define EXPAND(x) x << " "<<cos(x)<<" "<<exp(x)<<" "
#define EXPAND(x) x

int test_main(const char* input, const char* target, const char* outputfile)
{
    GPPtr<GLBmp> src = new GLBmp(input);
    GPPtr<GLBmp> dst = new GLBmp(target);
    GLASSERT(src->width() == dst->width());
    GLASSERT(dst->height() == src->height());
    std::string base(outputfile);
    auto r_file = base + "_r";
    auto g_file = base + "_g";
    auto b_file = base + "_b";
    std::ofstream r_output(r_file);
    std::ofstream g_output(g_file);
    std::ofstream b_output(b_file);
    int w = src->width();
    int h = dst->height();
    for (int i=0; i<h; ++i)
    {
        for (int j=0; j<w; ++j)
        {
            auto _src = src->getAddr(j, i);
            auto _dst = dst->getAddr(j, i);
            float r = _src[0]/255.0;
            float g = _src[1]/255.0;
            float b = _src[2]/255.0;
            float dr = _dst[0]/255.0;
            float dg = _dst[1]/255.0;
            float db = _dst[2]/255.0;
            r_output << dr << " "<<EXPAND(r) << " "<<EXPAND(g) <<" "<<EXPAND(b)<<"\n";
            g_output << dg << " "<<EXPAND(r) << " "<<EXPAND(g) <<" "<<EXPAND(b)<<"\n";
            b_output << db << " "<<EXPAND(r) << " "<<EXPAND(g) <<" "<<EXPAND(b)<<"\n";
        }
    }
    return 1;
}

int main(int argc, char* argv[])
{
    GLASSERT(argc>=4);
    return test_main(argv[1],argv[2], argv[3]);
}
