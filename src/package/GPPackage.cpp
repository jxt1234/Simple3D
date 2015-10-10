#include "GPPackage.h"
#include "GPTypes.h"
#include <assert.h>
#include "core/GLBmp.h"
#include "transform/GLColorMap.h"
GPContents* GLBmp_Psnr_GPpackage(GPContents* inputs)
{
assert(2 == inputs->size());
assert(inputs->contents[0].type == gGLBmp);
assert(inputs->contents[1].type == gGLBmp);
GPContents* out =  new GPContents;
GLBmp* X0 = (GLBmp*)inputs->get(0);
GLBmp* X1 = (GLBmp*)inputs->get(1);
double* result = new double;
*result = GLBmp_Psnr(X0, X1);
out->push(result,gdouble);
return out;
}
GPContents* GLColorMap_GPpackage(GPContents* inputs)
{
assert(2 == inputs->size());
assert(inputs->contents[0].type == gGLBmp);
assert(inputs->contents[1].type == gGLColorTable);
GPContents* out =  new GPContents;
GLBmp* X0 = (GLBmp*)inputs->get(0);
GLColorTable* X1 = (GLColorTable*)inputs->get(1);
GLBmp* result = GLColorMap(X0, X1);
out->push(result,gGLBmp);
return out;
}
