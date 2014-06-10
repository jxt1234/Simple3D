#ifndef FRAGMENT_GLWRITEPIXELS_H
#define FRAGMENT_GLWRITEPIXELS_H

#include "interface/IFragmentFunction.h"
#include "interface/IBitmap.h"

/*Color: 0.0~1.0, (rgba); pos: autual position (x,y)*/
void GLWritePixels(IBitmap* dst, IRasterizatedVarying* pos, IRasterizatedVarying* color);


#endif
