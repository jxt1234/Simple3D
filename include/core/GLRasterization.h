#ifndef CORE_RASTERIZATION_H
#define CORE_RASTERIZATION_H
#include "interface/IRasterizatedVarying.h"
#include "interface/IVarying.h"
#include "math/GLCurveSurface.h"
#include <vector>
#include "GLDepthBuffer.h"
#include <stdlib.h>

/*The first element of inputs must be GL_position*/
#ifdef __cplusplus
extern "C"{
#endif
//TODO support GL_TRIANGLES_STRIP type
void GLCSVertexGenerate(IVarying* pos, IVarying* normal, IVarying* tex, GLCurveSurface* cs, GLRectArea* area, int type);

void GLRasterization(std::vector<IVarying*> inputs, std::vector<IRasterizatedVarying*> outputs, int width, int height, GLDepthBuffer* buffer = NULL);
#ifdef __cplusplus
};
#endif



#endif
