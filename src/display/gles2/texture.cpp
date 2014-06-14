#include "display/texture.h"
#include "display/debug.h"
#include <GL/glew.h>


void texture::init()
{
    glGenTextures(1, &mId);
    OPENGL_CHECK_ERROR;
    glBindTexture(GL_TEXTURE_2D, mId);
    OPENGL_CHECK_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    OPENGL_CHECK_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    OPENGL_CHECK_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    OPENGL_CHECK_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    OPENGL_CHECK_ERROR;
}

void texture::upload(void* pixels, int w, int h)
{
    glBindTexture(GL_TEXTURE_2D, mId);
    OPENGL_CHECK_ERROR;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    OPENGL_CHECK_ERROR;
}

void texture::destory()
{
    glDeleteTextures(1, &mId);
    OPENGL_CHECK_ERROR;
    mId = 0;
}

void texture::use()
{
    glBindTexture(GL_TEXTURE_2D, mId);
}

void texture::use(int uniId, int texId)
{
}
