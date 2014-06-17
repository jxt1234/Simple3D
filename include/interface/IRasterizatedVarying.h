#ifndef INTERFACE_IRASTERIZATEDVARYING_H
#define INTERFACE_IRASTERIZATEDVARYING_H
#include "IBasicVarying.h"
class IRasterizatedVarying:public IBasicVarying
{
    public:
        INTERFACE(IRasterizatedVarying);
        /*For Rasterization*/
        //Add size number of unit to this IRasterizatedVarying
        virtual void alloc(int size) = 0;
        //Basic add method, it will copy input's unit number of value in the list
        virtual void add(float* input){}
};
#endif
