#ifndef SRC_PACKAGE_GPTYPES_H
#define SRC_PACKAGE_GPTYPES_H
#include "user/IStatusType.h"
extern IStatusType* gdouble;
extern IStatusType* gGLColorTable;
extern IStatusType* gGLBmp;
extern "C"{
IStatusType* GP_IStatusType_Create(const std::string& name);
}
#endif
