#ifndef DISPLAY_DEBUG_H
#define DISPLAY_DEBUG_H

#include <stdio.h>
#include "utils/GLDebug.h"
#include <assert.h>


#define OPENGL_CHECK_ERROR \
{GLenum error = glGetError();\
    if (GL_NO_ERROR!=error) \
    FUNC_PRINT_ALL(error, 0x); \
    GLASSERT(GL_NO_ERROR == error);}

#define OPENGL_HAS_ERROR \
    GL_NO_ERROR!=glGetError()

#endif
