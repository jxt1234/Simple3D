#include "core/GLGrayBitmap.h"
#include "utils/debug.h"
#include <string.h>
GLGrayBitmap::GLGrayBitmap(int w, int h)
{
    GLASSERT(0<w);
    GLASSERT(0<h);
    mPixels = new unsigned char[w*h];
    mW = w;
    mH = h;
    mOwnPixels = true;
}
GLGrayBitmap::GLGrayBitmap(unsigned char* pixels, int w, int h)
{
    GLASSERT(0<w);
    GLASSERT(0<h);
    mPixels = pixels;
    mW = w;
    mH = h;
    mOwnPixels = false;
}


GLGrayBitmap::~GLGrayBitmap()
{
    if (mOwnPixels)
    {
        delete [] mPixels;
    }
}
void GLGrayBitmap::clear()
{
    ::memset(mPixels, 0, mW*mH*sizeof(unsigned char));
}

/*0.3*r + 0.59*g + 0.11*b*/
/*(38*r + 76*g + 14*b)/128*/
void GLGrayBitmap::turnGray(GLGrayBitmap* dst, const GLBmp* src)
{
    GLASSERT(NULL!=dst);
    GLASSERT(NULL!=src);
    GLASSERT(src->width() == dst->width());
    GLASSERT(src->height() == dst->height());
    auto gray = dst->pixelsForWrite();
    auto rgb = (unsigned char*)(src->pixels());
    int w = src->width();
    int h = src->height();
    for (int i=0; i<h; ++i)
    {
        int sta = 0;
        auto gray_l = gray + i*w;
        auto rgb_l = rgb + i*w*4;
        for (int j=sta; j<w; ++j)
        {
            unsigned char r = rgb_l[j*4];
            unsigned char g = rgb_l[j*4+1];
            unsigned char b = rgb_l[j*4+2];
            gray_l[j] = (r*38 + g*76 + b*14) >> 7;
        }
    }
}
void GLGrayBitmap::turnRGB(const GLGrayBitmap* src, GLBmp* dst)
{
    GLASSERT(NULL!=dst);
    GLASSERT(NULL!=src);
    GLASSERT(src->width() == dst->width());
    GLASSERT(src->height() == dst->height());
    auto gray = src->pixelsForRead();
    auto rgb = (unsigned char*)(dst->pixels());
    int w = src->width();
    int h = src->height();
    for (int i=0; i<h; ++i)
    {
        int sta = 0;
        auto gray_l = gray + i*w;
        auto rgb_l = rgb + i*w*4;
        for (int j=sta; j<w; ++j)
        {
            auto ggray = gray_l[j];
            rgb_l[j*4] = ggray;
            rgb_l[j*4+1] = ggray;
            rgb_l[j*4+2] = ggray;
            rgb_l[j*4+3] = 255;
        }
    }
}

void GLGrayBitmap::mapRGB(const GLGrayBitmap* src, GLBmp* dst, unsigned char* rTab, unsigned char* gTab, unsigned char* bTab)
{
    GLASSERT(NULL!=dst);
    GLASSERT(NULL!=src);
    GLASSERT(src->width() == dst->width());
    GLASSERT(src->height() == dst->height());
    GLASSERT(NULL!=rTab);
    GLASSERT(NULL!=gTab);
    GLASSERT(NULL!=bTab);
    auto gray = src->pixelsForRead();
    auto rgb = (unsigned char*)(dst->pixels());
    int w = src->width();
    int h = src->height();
    for (int i=0; i<h; ++i)
    {
        int sta = 0;
        auto gray_l = gray + i*w;
        auto rgb_l = rgb + i*w*4;
        for (int j=sta; j<w; ++j)
        {
            auto ggray = gray_l[j];
            rgb_l[j*4] = rTab[ggray];
            rgb_l[j*4+1] = gTab[ggray];
            rgb_l[j*4+2] = bTab[ggray];
            rgb_l[j*4+3] = 255;
        }
    }
}


