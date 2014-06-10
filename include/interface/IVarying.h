#ifndef INTERFACL_IVARYING_H
#define INTERFACL_IVARYING_H

#include "IBasicVarying.h"
class IVarying:public IBasicVarying
{
    public:
        INTERFACE(IVarying);
        virtual float* alloc() = 0;
};

#endif
