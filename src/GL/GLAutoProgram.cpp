#include "GL/GLAutoProgram.h"

GLAutoProgram::GLAutoProgram(int proId)
{
    mId = proId;
    GLint previous;
    glGetIntegerv(GL_CURRENT_PROGRAM, &previous);
    OPENGL_CHECK_ERROR;
    mPrevious = previous;
    glUseProgram(proId);
    OPENGL_CHECK_ERROR;
}

GLAutoProgram::~GLAutoProgram()
{
    glUseProgram(mPrevious);
    OPENGL_CHECK_ERROR;
}
