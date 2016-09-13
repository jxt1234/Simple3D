#include "core/GLBmp.h"
#include "utils/GLDebug.h"
#include <string>
#include <fstream>
#include <GL/GLContext.h>
#include "GL/GLBitmapWork.h"
#include "GL/GLFilterWork.h"
using namespace std;
GPPtr<GLBmp> pretreat(GPPtr<GLBmp> src)
{
    return src;
    GLAutoContext __c;
    GPPtr<GLBmp> dst = new GLBmp(src->width(), src->height());
    {
        const float p[] = {0.1,0.2,0.4,0.2,0.1};
        int n = sizeof(p)/sizeof(float);
        GPPtr<GLTextureWork> _w = new GLFilterWork(p, n);
        GPPtr<GLBitmapWork> w = new GLBitmapWork(_w);
        w->set(src, dst);
        w->runOnePass();
    }
    return dst;
}

int main(int argc, char* argv[])
{
    GLASSERT(argc>=4);
    const char* rgbfile = argv[1];
    const char* blackfile = argv[2];
    const char* outputfile = argv[3];
    GPPtr<GLBmp> rgb_origin = new GLBmp(rgbfile);
    GPPtr<GLBmp> black = new GLBmp(blackfile);
    GPPtr<GLBmp> rgb = pretreat(rgb_origin);
    GLASSERT(rgb->width() == black->width());
    GLASSERT(rgb->height() == black->height());
    auto w = rgb->width();
    auto h = rgb->height();
    ofstream output(outputfile);
    GLASSERT(!output.fail());
    /*Find bound*/
    int t=h,b=0,l=w,r=0;
    for (auto i=0; i<h; ++i)
    {
        auto black_p = (unsigned char*)(black->pixels()) + 4*i*w;
        for (auto j=0; j<w; ++j)
        {
            if (black_p[4*j+1] > 100)
            {
                if (i<t) t=i;
                if (i>b) b=i;
                if (j<l) l=j;
                if (j>r) r=j;
            }
        }
    }
    for (auto i=t; i<=b; ++i)
    {
        auto black_p = (unsigned char*)(black->pixels()) + 4*(i*w);
        auto rgb_p = (unsigned char*)(rgb->pixels()) + 4*(i*w);
        for (auto j=l; j<=r; ++j)
        {
            int bl = black_p[4*j+1] <100 ? 0 : 1;
            float r = rgb_p[4*j+0]/255.0;
            float g = rgb_p[4*j+1]/255.0;
            float b = rgb_p[4*j+2]/255.0;
            float y = 0.30*r+0.59*g+0.11*b;
            float cb = 0.5*r - 0.4187*g -0.0813*b;
            float cr = -0.1687*r -0.3313*g + 0.5*b;
            float maxc = r > g?r:g;
            maxc = maxc > b ? maxc : b;
            float minc = r < g?r:g;
            minc = minc < b ? minc : b;
            float h=-1000,s,v;
            s = 1 - minc / maxc;
            v = maxc;
            if (maxc == r)
            {
                h = (g-b)/(maxc-minc);
            }
            else if (maxc == g)
            {
                h = 2 + (b-r)/(maxc-minc);
            }
            else if (b == maxc)
            {
                h = 4 + (r-g)/(maxc-minc);
            }
            if (maxc == minc)
            {
                h = 0.0;
                s = 1.0;
            }
            //output << bl << " "<<(float)rgb_p[0] <<" "<< (float)rgb_p[1] <<" "<< (float)rgb_p[2] << endl;
            //output << bl << " "<<cb <<" "<< cr << endl;
            output << bl;
            output << " "<< r << " "<<g <<" "<<b;
            output <<" "<<cb <<" "<< cr<< " "<< y;
            //output << " "<< h << " "<<s <<" "<<v;
            output <<endl;
        }
    }
    return 1;
}
