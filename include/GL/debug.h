#ifndef DISPLAY_DEBUG_H
#define DISPLAY_DEBUG_H

#include <stdio.h>
#include "utils/debug.h"
#include <assert.h>
#ifndef GL_BUILD_FOR_ANDROID
#define GLASSERT(x) assert(x)
#else
#define GLASSERT(x) \
    {bool result = (x);\
        if (!(result))\
        FUNC_PRINT((result));}
#endif


#define OPENGL_CHECK_ERROR \
{GLenum error = glGetError();\
    if (GL_NO_ERROR!=error) \
    FUNC_PRINT_ALL(error, 0x); \
    GLASSERT(GL_NO_ERROR == error);}


#endif
