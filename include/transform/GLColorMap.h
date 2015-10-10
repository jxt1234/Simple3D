#ifndef TRANSFORM_GLCOLORMAP_H
#define TRANSFORM_GLCOLORMAP_H
#include "core/GLBmp.h"
typedef GLBmp GLColorTable;
/*GP FUNCTION*/GLBmp* GLColorMap(GLBmp* src, GLColorTable* table/*S*/);
void GLColorMapInner(GLBmp* dst, const GLBmp* src, const GLBmp* table);

#endif
