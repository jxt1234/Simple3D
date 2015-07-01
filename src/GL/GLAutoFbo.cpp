#include "GL/GLAutoFbo.h"
GLAutoFbo::GLAutoFbo(GLTexture& dst)
{
    glGetIntegerv(GL_VIEWPORT, mViewPort);
    OPENGL_CHECK_ERROR;
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
    glViewport(mViewPort[0], mViewPort[1], mViewPort[2], mViewPort[3]);
    OPENGL_CHECK_ERROR;
}
