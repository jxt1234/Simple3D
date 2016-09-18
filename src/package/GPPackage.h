#ifndef SRC_PACKAGE_GPFUNCTIONS_H
#define SRC_PACKAGE_GPFUNCTIONS_H
#include "lowlevelAPI/GPContents.h"
extern "C"{
GPContents* GLBmp_Psnr_GPpackage(GPContents* inputs);
GPContents* GLColorMap_GPpackage(GPContents* inputs);
}
#endif
