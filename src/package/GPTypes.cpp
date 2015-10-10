#include "GPTypes.h"
#include "core/GLBmp.h"
#include "transform/GLColorMap.h"
#include "double_GPType.h"
IStatusType* gdouble = new double_GPType();
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
