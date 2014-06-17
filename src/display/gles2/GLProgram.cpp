#include "display/GLProgram.h"
#include <GL/glew.h>
#include <assert.h>

#include "display/debug.h"

static bool compileShader(GLuint s)
{
    GLint status;
    glCompileShader(s);
    glGetShaderiv(s, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        int len;
        glGetShaderiv(s, GL_INFO_LOG_LENGTH, &len);
        char* buffer = new char[len+1];
        glGetShaderInfoLog(s, len, NULL, buffer);
        buffer[len] = 0;
        FUNC_PRINT_ALL(buffer, s);
        delete [] buffer;
        return false;
    }
    return true;
}

CONTEXT_API void GLProgram::init()
{
    if (mInit) return;
    /*Create Shader*/
    GLint vert = glCreateShader(GL_VERTEX_SHADER);
    OPENGL_CHECK_ERROR;
    GLint frag = glCreateShader(GL_FRAGMENT_SHADER);
    OPENGL_CHECK_ERROR;
    const char* _ver[1];
    const char* _frag[1];
    _ver[0] = mVertex;
    _frag[0] = mFragment;
    glShaderSource(vert, 1, _ver, NULL);
    OPENGL_CHECK_ERROR;
    glShaderSource(frag, 1, _frag, NULL);
    OPENGL_CHECK_ERROR;
    /*TODO move assert to be log*/
    assert(compileShader(vert));
    assert(compileShader(frag));
    /*Create Program*/
    mId = glCreateProgram();
    OPENGL_CHECK_ERROR;
    glAttachShader(mId, vert);
    OPENGL_CHECK_ERROR;
    glAttachShader(mId, frag);
    OPENGL_CHECK_ERROR;
    glLinkProgram(mId);
    OPENGL_CHECK_ERROR;
    GLint linked;
    glGetProgramiv(mId, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        FUNC_PRINT(linked);
    }
    mInit = true;
    mVertId = vert;
    mFragId = frag;
}

CONTEXT_API int GLProgram::attr(const char* name)
{
    assert(NULL!=name && 0!=mId);
    return glGetAttribLocation(mId, name);
}
CONTEXT_API int GLProgram::uniform(const char* name)
{
    assert(NULL!=name && 0!=mId);
    return glGetUniformLocation(mId, name);
}
CONTEXT_API void GLProgram::destroy()
{
    if (!mInit) return;
    glDeleteProgram(mId);
    glDeleteShader(mVertId);
    glDeleteShader(mFragId);
    mInit = false;
}

CONTEXT_API void GLProgram::use()
{
    if (!mInit)
    {
        init();
    }
    glUseProgram(mId);
}
void GLProgram::setMatrix(const GLMatrix4& matrix, int id)
{
    float tempMatrix[16];
    matrix.copy(tempMatrix);
    glUniformMatrix4fv(id, 1, GL_FALSE, tempMatrix);
}
void GLProgram::setUniform(int value, int id)
{
    glUniform1i(id, value);
}

void GLProgram::setUniform(float value, int id)
{
    glUniform1f(id, value);
}
