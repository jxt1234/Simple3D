#ifndef INCLUDE_UTILS_REFCOUNT_H
#define INCLUDE_UTILS_REFCOUNT_H
#include <stdlib.h>
#include "lowlevelAPI/GPRefCount.h"
#define SAFE_UNREF(x)\
    if (NULL!=(x)) {(x)->decRef();}
#define SAFE_REF(x)\
    if (NULL!=(x)) (x)->addRef();

#define SAFE_ASSIGN(dst, src) \
    {\
        if (src!=NULL)\
        {\
            src->addRef();\
        }\
        if (dst!=NULL)\
        {\
            dst->decRef();\
        }\
        dst = src;\
    }

typedef GPRefCount RefCount;

#endif
