#ifndef DISPLAY_HEAD_H
#define DISPLAY_HEAD_H

/*This mean the function can just be called in the opengl Context*/
#define CONTEXT_API
/*This mean the class should be used only in opengl context thread*/
#define CONTEXT_CLASS
/*If defined this, means the method of a CONTEXT_CLASS can be called outside context*/
#define CONTEXT_FREE_API
#include <stdlib.h>
#include <assert.h>
#ifdef GL_BUILD_FOR_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#else
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#endif
#endif
#include "debug.h"
#include "utils/RefCount.h"
#define OPENGL_ASSERT(x) assert(x)

#endif
