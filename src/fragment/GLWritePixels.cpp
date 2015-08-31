#include "fragment/GLWritePixels.h"
#include <assert.h>
void GLWritePixels(IBitmap* dst, IRasterizatedVarying* pos, IRasterizatedVarying* color)
{
    assert(NULL!=dst);
    assert(NULL!=pos);
    assert(NULL!=color);
    assert(pos->size() == color->size());
    int w = dst->width();
    int h = dst->height();
    for (int i=0; i<pos->size(); ++i)
    {
        float* p = pos->load(i);
        int x = p[0]*w;
        int y = p[1]*h;
        if (x>=w) x=w-1;
        if (y>=h) y=h-1;
        float* c = color->load(i);
        GLColor color;
        color.r = c[0]*255;
        color.g = c[1]*255;
        color.b = c[2]*255;
        color.a = c[3]*255;
        dst->setColor(color, x, y);
    }
}
