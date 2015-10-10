#ifndef CORE_GLGRAYBITMAP_H
#define CORE_GLGRAYBITMAP_H
#include "GLBmp.h"
class GLGrayBitmap:public RefCount
{
public:
    /*Alloc new pixels*/
    GLGrayBitmap(int w, int h);
    /*Create Gray Bitmap from outside pixels*/
    GLGrayBitmap(unsigned char* pixels, int w, int h);
    virtual ~GLGrayBitmap();
    inline int bpp() const {return 1;}
    inline int stride() const {return width()*bpp()*sizeof(unsigned char);}
    inline int width() const {return mW;}
    inline int height() const {return mH;}
    inline unsigned char* getAddr(int x, int y) const {return mPixels+y*mW+x;}
    inline unsigned char* pixelsForWrite() {return mPixels;}
    inline const unsigned char* pixelsForRead() const {return mPixels;}
    static void turnGray(GLGrayBitmap* dst, const GLBmp* src);
    static void turnRGB(const GLGrayBitmap* src, GLBmp* dst);
    static void mapRGB(const GLGrayBitmap* src, GLBmp* dst, unsigned char* rTab, unsigned char* gTab, unsigned char* bTab);
    void clear();
private:
    unsigned char* mPixels;
    int mW;
    int mH;
    bool mOwnPixels;
};
#endif
