
#ifndef INTERFACE_IBASICVARYING_H
#define INTERFACE_IBASICVARYING_H
#include "head.h"

class IBasicVarying
{
    public:
        INTERFACE(IBasicVarying);
        virtual float* load(int pos) = 0;//Get the pointer of data in the pos position
        virtual int unit() = 0;//One element's size
        virtual int size() = 0;//The number of elements
};


#endif
