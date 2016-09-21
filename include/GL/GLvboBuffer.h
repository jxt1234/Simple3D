#ifndef DISPLAY_VBOBUFFER_H
#define DISPLAY_VBOBUFFER_H

#include "head.h"
#include "interface/IVarying.h"
#include <vector>
#include "utils/RefCount.h"
/*Only Support float arrays*/

class GLvboBuffer:public RefCount
{
public:
    inline void setType(int t){mType = t;}
    /*unit*size*sizeof(float) = sizeof(b)*/
    CONTEXT_API GLvboBuffer(const float* buffer, int unit, int size, int type = GL_TRIANGLES);
    CONTEXT_API GLvboBuffer(IVarying* buffer, int type = GL_TRIANGLES);
    CONTEXT_API ~GLvboBuffer();
    CONTEXT_API void use(int id);
    CONTEXT_API void use(int id, int subUnit, int offset);
    CONTEXT_API void draw();
    /*off and len is counted by points*/
    CONTEXT_API void update(float* subBuffer, int off, int len);
    CONTEXT_API void update(IVarying* buffer, int off, int staBuffer, int finBuffer);
    CONTEXT_API static void reset();
    inline int size(){return mSize;}
private:
    unsigned int mId;
    int mUnit;
    int mSize;
    int mType;
};

#endif
