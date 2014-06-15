#include "core/GLBmp.h"
#include "utils/debug.h"
static const int mBpp = 4;

GLBmp::GLBmp(int w, int h)
{
    mBitmap = FreeImage_Allocate(w, h, mBpp*8);
    mWidth = w;
    mHeight = h;
}

GLBmp::~GLBmp()
{
    if (NULL!=mBitmap)
    {
        FreeImage_Unload(mBitmap);
    }
}

void GLBmp::save(const char* path)
{
    assert(NULL!=mBitmap);
    assert(NULL!=path);
    FreeImage_Save(FIF_PNG, mBitmap, path, PNG_DEFAULT);
}

GLColor GLBmp::getColor(int x, int y)
{
    BYTE *bitsLine = FreeImage_GetScanLine(mBitmap, y) + mBpp * x;
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
    BYTE *bitsLine = FreeImage_GetScanLine(mBitmap, y) + mBpp * x;
    bitsLine[FI_RGBA_RED] = c.r;
    bitsLine[FI_RGBA_GREEN] = c.g;
    bitsLine[FI_RGBA_BLUE] = c.b;
    bitsLine[FI_RGBA_ALPHA] = c.a;
}

void GLBmp::loadPicture(const char* pic)
{
    /*Just support png*/
    FIBITMAP* bitmap = FreeImage_Load(FIF_PNG, pic, PNG_DEFAULT);
    mBitmap = FreeImage_ConvertTo32Bits(bitmap);
    FreeImage_Unload(bitmap);
    mWidth  = FreeImage_GetWidth(mBitmap);
    mHeight = FreeImage_GetHeight(mBitmap);
}
