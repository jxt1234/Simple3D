#ifndef TRANSFORM_GLBASICTRANSFORM_H
#define TRANSFORM_GLBASICTRANSFORM_H

/*API*/
#include "interface/IBitmap.h"

extern "C"{

void GLRotate(IBitmap& src, IBitmap& dst, float degree, bool scale = false);

};



#endif
