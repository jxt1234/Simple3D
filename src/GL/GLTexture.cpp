#include "GL/GLTexture.h"
#include "GL/debug.h"

GLTexture::GLTexture()
{
    mId = 0;
    init();
    mW = 0;
    mH = 0;
}

GLTexture::~GLTexture()
{
    destory();
}

void GLTexture::init()
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

void GLTexture::upload(void* pixels, int w, int h)
{
    glBindTexture(GL_TEXTURE_2D, mId);
    OPENGL_CHECK_ERROR;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    OPENGL_CHECK_ERROR;
    mW = w;
    mH = h;
}
void GLTexture::download(void* pixels)
{
    assert(mW>0 && mH>0);
    /*TODO Use glPixelStorei to determine align*/
    glReadPixels(0, 0, mW, mH, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    OPENGL_CHECK_ERROR;
}

void GLTexture::destory()
{
    glDeleteTextures(1, &mId);
    OPENGL_CHECK_ERROR;
    mId = 0;
}

void GLTexture::use()
{
    glActiveTexture(0);
    OPENGL_CHECK_ERROR;
    glBindTexture(GL_TEXTURE_2D, mId);
    OPENGL_CHECK_ERROR;
}

void GLTexture::use(int uniId, int texId)
{
    glActiveTexture(texId);
    OPENGL_CHECK_ERROR;
    glUniform1i(uniId, texId);
    OPENGL_CHECK_ERROR;
    glBindTexture(GL_TEXTURE_2D, mId);
    OPENGL_CHECK_ERROR;
}
