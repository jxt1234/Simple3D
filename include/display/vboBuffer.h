#ifndef DISPLAY_VBOBUFFER_H
#define DISPLAY_VBOBUFFER_H

#include "head.h"
#include "interface/IVarying.h"
/*Only Support float arrays*/

class vboBuffer
{
    public:
        /*unit*size*sizeof(float) = sizeof(b)*/
        CONTEXT_API vboBuffer(float* buffer, int unit, int size);
        CONTEXT_API vboBuffer(IVarying* buffer);
        CONTEXT_API ~vboBuffer();
        CONTEXT_API void use(int id);
        /*off and len is counted by points*/
        CONTEXT_API void update(float* subBuffer, int off, int len);
        CONTEXT_API void update(IVarying* buffer, int off, int staBuffer, int finBuffer);
        CONTEXT_API static void reset();
        inline int size(){return mSize;}
    private:
        unsigned int mId;
        int mUnit;
        int mSize;
};

#endif
