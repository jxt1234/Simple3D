#ifndef DISPLAY_DEBUG_H
#define DISPLAY_DEBUG_H

#include <stdio.h>
#include "utils/debug.h"

#define OPENGL_CHECK_ERROR \
{GLenum error = glGetError();\
    if (GL_NO_ERROR!=error) \
    FUNC_PRINT_ALL(error, 0x); \
    assert(GL_NO_ERROR == error);}


#endif
