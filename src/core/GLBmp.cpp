#include "core/GLBmp.h"
#include "utils/debug.h"
#include "utils/GP_Clock.h"
#include "../third_party/FreeImage/Source/FreeImage.h"
#include <math.h>
static const int gBpp = 4;

GLBmp::GLBmp(int w, int h)
{
    mBitmap = FreeImage_Allocate(w, h, gBpp*8);
    mWidth = w;
    mHeight = h;
}

GLBmp::~GLBmp()
{
    GLASSERT(NULL!=mBitmap);
    FreeImage_Unload(mBitmap);
}

GLBmp::GLBmp(const char* pic)
{
    FREE_IMAGE_FORMAT f = FreeImage_GetFileType(pic);
    FIBITMAP* bitmap = FreeImage_Load(f, pic);
    mBitmap = FreeImage_ConvertTo32Bits(bitmap);
    FreeImage_Unload(bitmap);
    mWidth  = FreeImage_GetWidth(mBitmap);
    mHeight = FreeImage_GetHeight(mBitmap);
}
GLBmp::GLBmp(unsigned char* data, int length)
{
    FIMEMORY* memory = FreeImage_OpenMemory(data, length);
    FREE_IMAGE_FORMAT f = FreeImage_GetFileTypeFromMemory(memory, length);
    FIBITMAP* bitmap = FreeImage_LoadFromMemory(f, memory);
    FreeImage_CloseMemory(memory);
    mBitmap = FreeImage_ConvertTo32Bits(bitmap);
    FreeImage_Unload(bitmap);
    mWidth  = FreeImage_GetWidth(mBitmap);
    mHeight = FreeImage_GetHeight(mBitmap);
}



void GLBmp::save(const char* path)
{
    assert(NULL!=mBitmap);
    assert(NULL!=path);
    FreeImage_Save(FIF_PNG, mBitmap, path, PNG_DEFAULT);
}

GLColor GLBmp::getColor(int x, int y)
{
    BYTE *bitsLine = FreeImage_GetScanLine(mBitmap, y) + gBpp * x;
    GLColor c;
    c.r = bitsLine[FI_RGBA_RED];
    c.g = bitsLine[FI_RGBA_GREEN];
    c.b = bitsLine[FI_RGBA_BLUE];
    c.a = bitsLine[FI_RGBA_ALPHA];
    return c;
}

void* GLBmp::pixels() const
{
    return (void*)FreeImage_GetScanLine(mBitmap, 0);
}

void GLBmp::setColor(const GLColor& c, int x, int y)
{
    BYTE *bitsLine = FreeImage_GetScanLine(mBitmap, y) + gBpp * x;
    bitsLine[FI_RGBA_RED] = c.r;
    bitsLine[FI_RGBA_GREEN] = c.g;
    bitsLine[FI_RGBA_BLUE] = c.b;
    bitsLine[FI_RGBA_ALPHA] = c.a;
}

double GLBmp::psnr(const GLBmp& other) const
{
    //GPCLOCK;
    double result = 0.0;
    int w = other.width();
    int h = other.height();
    if (width()!=w || height()!=h)
    {
        return 0.0;
    }
    unsigned char* src = (unsigned char*)pixels();
    unsigned char* dst = (unsigned char*)other.pixels();
    for (int i=0; i<h; ++i)
    {
        for (int j=0; j<w; ++j)
        {
            for (int k=0; k<3; ++k)
            {
                double s = src[k];
                double d = dst[k];
                result+= (s-d)*(s-d);
            }
            src+=4;
            dst+=4;
        }
    }
    unsigned char _max = 0xFF;
    result = result/(double)(w*h*3);
    result = -10.0*log(result/(double)_max/(double)_max)/log(10.0);
    return result;
}
unsigned char* GLBmp::getAddr(int x, int y) const
{
    return (unsigned char*)pixels() + (y*mWidth+x)*bpp();
}

double GLBmp_Psnr(const GLBmp* src, const GLBmp* dst)
{
    GLASSERT(NULL!=src);
    GLASSERT(NULL!=dst);
    GLASSERT(src->width() == dst->width());
    GLASSERT(src->height() == dst->height());
    return src->psnr(*dst);
}

