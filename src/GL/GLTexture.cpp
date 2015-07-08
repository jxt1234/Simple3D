#include "GL/GLTexture.h"
#include "GL/debug.h"

GLTexture::GLTexture(int target)
{
    mTarget = target;
    mId = 0;
    mW = 0;
    mH = 0;
    init();
}
GLTexture::GLTexture(int id, int w, int h, int target)
{
    mTarget = target;
    mId = id;
    mW = w;
    mH = h;
}

GLTexture::~GLTexture()
{
    destory();
}

void GLTexture::init()
{
    glGenTextures(1, &mId);
    OPENGL_CHECK_ERROR;
    glBindTexture(mTarget, mId);
    OPENGL_CHECK_ERROR;
    glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    OPENGL_CHECK_ERROR;
    glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    OPENGL_CHECK_ERROR;
    glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    OPENGL_CHECK_ERROR;
    glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    OPENGL_CHECK_ERROR;
}

void GLTexture::setFilter(bool filter)
{
    glBindTexture(mTarget, mId);
    OPENGL_CHECK_ERROR;
    if (filter)
    {
        glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        OPENGL_CHECK_ERROR;
        glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        OPENGL_CHECK_ERROR;
    }
    else
    {
        glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        OPENGL_CHECK_ERROR;
        glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        OPENGL_CHECK_ERROR;
    }
}

void GLTexture::upload(void* pixels, int w, int h)
{
    glBindTexture(mTarget, mId);
    OPENGL_CHECK_ERROR;
    glTexImage2D(mTarget, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
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
    glActiveTexture(GL_TEXTURE0);
    OPENGL_CHECK_ERROR;
    glBindTexture(mTarget, mId);
    OPENGL_CHECK_ERROR;
}

void GLTexture::use(int uniId, int texId)
{
    glActiveTexture(GL_TEXTURE0+texId);
    OPENGL_CHECK_ERROR;
    glUniform1i(uniId, texId);
    OPENGL_CHECK_ERROR;
    glBindTexture(mTarget, mId);
    OPENGL_CHECK_ERROR;
}
