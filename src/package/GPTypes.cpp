#include "GPTypes.h"
#include "core/GLBmp.h"
#include "transform/GLColorMap.h"
IStatusType* gdouble = new GPDoubleType();
#include "GLColorTable_GPType.h"
IStatusType* gGLColorTable = new GLColorTable_GPType();
#include "GLBmp_GPType.h"
IStatusType* gGLBmp = new GLBmp_GPType();
IStatusType* GP_IStatusType_Create(const std::string& name)
{
if (name == "double")
{
return gdouble;
}
if (name == "GLColorTable")
{
return gGLColorTable;
}
if (name == "GLBmp")
{
return gGLBmp;
}
return NULL;
}
