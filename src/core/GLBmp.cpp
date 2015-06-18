#include "core/GLBmp.h"
#include "utils/debug.h"
#include <math.h>
static const int gARGB_Bpp = 4;

GLBmp::GLBmp(int w, int h)
{
    GLASSERT(w>0 && h>0);
    mAttr.width = w;
    mAttr.height = h;
    mAttr.bpp = gARGB_Bpp;
    mAttr.stride = w;
    mPixels = new uint32_t[w*h];
}

GLBmp::~GLBmp()
{
    delete [] mPixels;
}


/*
void GLBmp::loadPicture(unsigned char* data, int length)
{
    FIMEMORY* memory = FreeImage_OpenMemory(data, length);
    FREE_IMAGE_FORMAT f = FreeImage_GetFileTypeFromMemory(memory, length);
    FIBITMAP* bitmap = FreeImage_LoadFromMemory(f, memory);
    FreeImage_CloseMemory(memory);

    if (NULL!=mBitmap)
    {
        FreeImage_Unload(mBitmap);
    }
    mBitmap = FreeImage_ConvertTo32Bits(bitmap);
    FreeImage_Unload(bitmap);

    mWidth  = FreeImage_GetWidth(mBitmap);
    mHeight = FreeImage_GetHeight(mBitmap);
}

void GLBmp::loadPicture(const char* pic)
{
    FREE_IMAGE_FORMAT f = FreeImage_GetFileType(pic);
    FIBITMAP* bitmap = FreeImage_Load(f, pic);
    if (NULL!=mBitmap)
    {
        FreeImage_Unload(mBitmap);
    }
    mBitmap = FreeImage_ConvertTo32Bits(bitmap);
    FreeImage_Unload(bitmap);
    mWidth  = FreeImage_GetWidth(mBitmap);
    mHeight = FreeImage_GetHeight(mBitmap);
}
*/
double GLBmp::psnr(const GLBmp& other)
{
    double result = 0.0;
    auto attr = other.vGetAttribute();
    int w = attr.width;
    int h = attr.height;
    if (mAttr.width!=w || mAttr.height!=h || mAttr.bpp != attr.bpp)
    {
        /*TODO scale into same size for compare*/
        return 0.0;
    }
    for (int i=0; i<h; ++i)
    {
        uint32_t* src = mPixels + w*i;
        uint32_t* dst = (uint32_t*)other.vGetAddr(0, i);
        for (int j=0; j<w; ++j)
        {
            double s = *src++;
            double d = *dst++;
            result+= (s-d)*(s-d);
        }
    }
    uint32_t _max = 0xFFFFFFFF;
    result = result/(double)(w*h);
    result = -10.0*log(result/(double)_max/(double)_max)/log(10.0);
    return result;
}
