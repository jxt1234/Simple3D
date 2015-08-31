#ifndef CORE_GLGRAYBITMAP_H
#define CORE_GLGRAYBITMAP_H
#include "GLBmp.h"
class GLGrayBitmap:public RefCount
{
public:
    GLGrayBitmap(int w, int h);
    virtual ~GLGrayBitmap();
    inline int width() const {return mW;}
    inline int height() const {return mH;}
    inline unsigned char* pixelsForWrite() {return mPixels;}
    inline const unsigned char* pixelsForRead() const {return mPixels;}
    static void turnGray(GLGrayBitmap* dst, const GLBmp* src);
    static void turnRGB(const GLGrayBitmap* src, GLBmp* dst);
private:
    unsigned char* mPixels;
    int mW;
    int mH;
};
#endif
