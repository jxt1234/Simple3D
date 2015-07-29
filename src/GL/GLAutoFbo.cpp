#include "GL/GLAutoFbo.h"
GLAutoFbo::GLAutoFbo(GLTexture& dst)
{
    mEnableClip = glIsEnabled(GL_SCISSOR_TEST);
    OPENGL_CHECK_ERROR;
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
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, dst.target(), dst.id(), 0);
    OPENGL_CHECK_ERROR;
    glViewport(0,0,dst.width(), dst.height());
    OPENGL_CHECK_ERROR;
    glDisable(GL_SCISSOR_TEST);
}
GLAutoFbo::~GLAutoFbo()
{
    glBindFramebuffer(GL_FRAMEBUFFER, mPrevious);
    OPENGL_CHECK_ERROR;
    glDeleteFramebuffers(1, &mId);
    OPENGL_CHECK_ERROR;
    glViewport(mViewPort[0], mViewPort[1], mViewPort[2], mViewPort[3]);
    OPENGL_CHECK_ERROR;
    if (mEnableClip)
    {
        glEnable(GL_SCISSOR_TEST);
    }
}
