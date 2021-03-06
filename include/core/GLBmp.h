#ifndef CORE_GLBMP_H
#define CORE_GLBMP_H

#include <stdlib.h>
#include <stdint.h>
#include "interface/IBitmap.h"
class FIBITMAP;

/*Only one color format ARGB*/
class GLBmp:public IBitmap
{
public:
    GLBmp(int w, int h);
    GLBmp(const char* pic);
    GLBmp(int w, int h, void* data);
    GLBmp(unsigned char* data, int length);
    void save(const char* path);
    void* pixels() const;
    unsigned char* getAddr(int x, int y) const;
    inline int bpp() const {return 4;}
    inline int stride() const {return width()*bpp()*sizeof(unsigned char);}
    //
    virtual ~GLBmp();
    virtual GLColor getColor(int x, int y);
    virtual void setColor(const GLColor& c, int x, int y);
    
    double psnr(const GLBmp& other) const;
    
    static void loadComponent(unsigned char* pix[], const GLBmp* src, size_t pix_stride, size_t offset);
    static void writeComponent(unsigned char* pix[], GLBmp* dst, size_t pix_stride, size_t offset);
protected:
    FIBITMAP* mBitmap;
};

#endif
