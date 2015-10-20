#include "core/GLBitmapFactory.h"
#include "../third_party/FreeImage/Source/FreeImage.h"
#include <string.h>

static GLBmp* _convert(FIBITMAP* mBitmap)
{
    auto w  = FreeImage_GetWidth(mBitmap);
    auto h = FreeImage_GetHeight(mBitmap);
    GLBmp* result = new GLBmp(w, h);
    for (int y=0; y<h; ++y)
    {
        auto src = FreeImage_GetScanLine(mBitmap, y);
        auto dst = result->getAddr(0, y);
        ::memcpy(dst, src, w*4*sizeof(char));
    }
    return result;
}

static FIBITMAP* _convertR(const GLBmp* srcs)
{
    auto w  = srcs->width();
    auto h = srcs->height();
    auto mBitmap = FreeImage_Allocate(w, h, 32);
    for (int y=0; y<h; ++y)
    {
        auto src = srcs->getAddr(0, y);
        auto dst = FreeImage_GetScanLine(mBitmap, y);
        ::memcpy(dst, src, w*4*sizeof(char));
    }
    return mBitmap;
}

GLBmp* GLBitmapFactory::create(const char* pic)
{
    FREE_IMAGE_FORMAT f = FreeImage_GetFileType(pic);
    FIBITMAP* bitmap = FreeImage_Load(f, pic);
    auto mBitmap = FreeImage_ConvertTo32Bits(bitmap);
    FreeImage_Unload(bitmap);
    auto result = _convert(mBitmap);
    FreeImage_Unload(mBitmap);
    return result;
}
GLBmp* create(unsigned char* data, int length)
{
    FIMEMORY* memory = FreeImage_OpenMemory(data, length);
    FREE_IMAGE_FORMAT f = FreeImage_GetFileTypeFromMemory(memory, length);
    FIBITMAP* bitmap = FreeImage_LoadFromMemory(f, memory);
    FreeImage_CloseMemory(memory);
    auto mBitmap = FreeImage_ConvertTo32Bits(bitmap);
    FreeImage_Unload(bitmap);
    auto result = _convert(mBitmap);
    FreeImage_Unload(mBitmap);
    return result;
}
void GLBitmapFactory::dump(const GLBmp* bmp, const char* filename)
{
    auto bitmap = _convertR(bmp);
    FreeImage_Save(FIF_PNG, bitmap, filename, PNG_DEFAULT);
    FreeImage_Unload(bitmap);
}
