#ifndef CORE_GLBMP_H
#define CORE_GLBMP_H

#include <stdlib.h>
#include <stdint.h>
#include "interface/IBitmap.h"
#include "interface/GLColor.h"

/*Only one color format ARGB*/
class GLBmp:public IBitmap
{
public:
    GLBmp(int w, int h);
    virtual void* vGetAddr(int x, int y) const
    {
        return mPixels + mAttr.stride*y + x;
    }
    virtual const Attribute& vGetAttribute() const {return mAttr;}
    virtual ~GLBmp();
    
    double psnr(const GLBmp& other);
private:
    uint32_t* mPixels;
    Attribute mAttr;
};


#endif
