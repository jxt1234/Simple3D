#include "GL/GLAutoFbo.h"
//FIXME Store viewport and revert
GLAutoFbo::GLAutoFbo(GLTexture& dst)
{
    GLint previous;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previous);
    mPrevious = previous;
    OPENGL_CHECK_ERROR;
    glGenFramebuffers(1, &mId);
    OPENGL_CHECK_ERROR;
    glBindFramebuffer(GL_FRAMEBUFFER, mId);
    OPENGL_CHECK_ERROR;
    dst.use();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, dst.id(), 0);
    OPENGL_CHECK_ERROR;
    glViewport(0,0,dst.width(), dst.height());
    OPENGL_CHECK_ERROR;
}
GLAutoFbo::~GLAutoFbo()
{
    glBindFramebuffer(GL_FRAMEBUFFER, mPrevious);
    OPENGL_CHECK_ERROR;
    glDeleteFramebuffers(1, &mId);
    OPENGL_CHECK_ERROR;
}
