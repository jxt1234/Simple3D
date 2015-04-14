#ifndef INTERFACE_IBITMAP_H
#define INTERFACE_IBITMAP_H
#include <stdlib.h>
#include <assert.h>
#include "utils/RefCount.h"
#include "head.h"
class IBitmap:public RefCount
{
public:
    struct Attribute
    {
        int width;
        int height;
        int stride;
        int bpp;
    };
    INTERFACE(IBitmap);
    virtual void* vGetAddr(int x, int y) const = 0;
    virtual const Attribute& vGetAttribute() const = 0;
    inline int getWidth() const {return vGetAttribute().width;}
    inline int getHeight() const {return vGetAttribute().height;}
    inline int getStride() const {return vGetAttribute().stride;}
    inline int getBpp() const {return vGetAttribute().bpp;}
};


#endif
