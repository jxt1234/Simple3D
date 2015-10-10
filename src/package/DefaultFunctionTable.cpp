#include "package/DefaultFunctionTable.h"
#include "GPPackage.h"
#include "GPTypes.h"
void* DefaultFunctionTable::vGetFunction(const std::string& name)
{
if (name == "GLBmp_Psnr_GPpackage")
{
return (void*)GLBmp_Psnr_GPpackage;
}
if (name == "GLColorMap_GPpackage")
{
return (void*)GLColorMap_GPpackage;
}
if (name == "GP_IStatusType_Create")
{
return (void*)GP_IStatusType_Create;
}
return NULL;
}
