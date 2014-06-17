#ifndef DISPLAY_GLOBJECT_H
#define DISPLAY_GLOBJECT_H
#include "utils/RefCount.h"
#include "math/GLMatrix4.h"
#include "head.h"

class CONTEXT_CLASS GLObject:public RefCount
{
    public:
        GLObject(){}
        virtual ~GLObject(){}
        virtual void onDraw(const GLMatrix4& transform, const GLMatrix4& projection) = 0;
};

#endif
