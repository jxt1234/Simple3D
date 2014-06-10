#ifndef PACkAGE_FRAGMENT_H
#define PACkAGE_FRAGMENT_H
#include "package.h"
extern "C"
{
    GP_Output GLPackageTexture2D(GP_Input inputs);
    GP_Output GLPackageWritePixels(GP_Input inputs);
    GP_Output GLPackageSingleLight(GP_Input inputs);
};





#endif
