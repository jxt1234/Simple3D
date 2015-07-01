#include "GL/GLProgram.h"
#include <sstream>
#include <fstream>
#include <string.h>
using namespace std;

GLProgram::GLProgram()
{
    mId = 0;
    mInit = false; 
}

void GLProgram::load(const std::string& vertex, const std::string& frag)
{
    GLAutoLock _l(mLock);
    mInit = false;
    mVertex = vertex;
    mFragment = frag;
}

void GLProgram::load(const char* vex, const char* frag)
{
    GLASSERT(NULL!=vex);
    GLASSERT(NULL!=frag);
    mVertex = vex;
    mFragment = frag;
    mInit = false;
}

static string loadAllContent(const char* file)
{
    ifstream is(file);
    ostringstream os;
    os << is.rdbuf();
    return os.str();
}

void GLProgram::loadFiles(const char* vertex, const char* frag)
{
    GLASSERT(NULL!=vertex);
    GLASSERT(NULL!=frag);
    mInit = false;
    mVertex = loadAllContent(vertex);
    mFragment = loadAllContent(frag);
}

GLProgram::GLProgram(const std::string& vertex, const std::string& frag)
{
    mInit = false;
    mId = 0;
    load(vertex, frag);
}

GLProgram::~GLProgram()
{
    destroy();
    ///*If the GLProgram is not destroy before, it shouldn't be freed*/
    GLASSERT(!mInit);
}
static bool compileShader(GLuint s)
{
    GLint status;
    glCompileShader(s);
    glGetShaderiv(s, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        int len;
        glGetShaderiv(s, GL_INFO_LOG_LENGTH, &len);
        if (0>=len)
        {
            glGetShaderInfoLog(s, 0, &len, NULL);
        }
        char* buffer = new char[len+1];
        glGetShaderInfoLog(s, len, NULL, buffer);
        buffer[len] = 0;
        FUNC_PRINT_ALL(buffer, s);
        delete [] buffer;
        return false;
    }
    return true;
}

CONTEXT_API bool GLProgram::init()
{
    if (mInit) return true;
    GLAutoLock _l(mLock);
    /*Create Shader*/
    GLint vert = glCreateShader(GL_VERTEX_SHADER);
    OPENGL_CHECK_ERROR;
    GLint frag = glCreateShader(GL_FRAGMENT_SHADER);
    OPENGL_CHECK_ERROR;
    const char* _ver[1];
    const char* _fra[1];
    _ver[0] = mVertex.c_str();
#ifdef GL_BUILD_FOR_ANDROID
    ostringstream newfra;
    newfra << "precision mediump float;\n"<<mFragment;
    _fra[0] = newfra.str().c_str();
#else
    _fra[0] = mFragment.c_str();
#endif
    glShaderSource(vert, 1, _ver, NULL);
    OPENGL_CHECK_ERROR;
    glShaderSource(frag, 1, _fra, NULL);
    OPENGL_CHECK_ERROR;
    /*TODO move GLASSERT to be log*/
    bool res = compileShader(vert);
    //if (!res) FUNC_PRINT_ALL(mVertex.c_str(), s);
    GLASSERT(true == res);
    if (false == res) return false;
    res = (compileShader(frag));
    //if (!res) FUNC_PRINT_ALL(mFragment.c_str(), s);
    GLASSERT(true == res);
    if (false == res) return false;
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
        GLsizei len;
        glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &len);
        if (len <=0)
        {
            glGetProgramInfoLog(mId, 0, &len, NULL);
        }
        if (len > 0)
        {
            char* buffer = new char[len+1];
            buffer[len] = '\0';
            glGetProgramInfoLog(mId, len, NULL, buffer);
            FUNC_PRINT_ALL(buffer, s);
            delete [] buffer;
        }
        return false;
    }
    mInit = true;
    mVertId = vert;
    mFragId = frag;
    return true;
}

CONTEXT_API int GLProgram::attr(const char* name) const
{
    GLASSERT(NULL!=name && 0!=mId);
    return glGetAttribLocation(mId, name);
}
CONTEXT_API int GLProgram::uniform(const char* name) const
{
    GLASSERT(NULL!=name && 0!=mId);
    return glGetUniformLocation(mId, name);
}
CONTEXT_API void GLProgram::destroy()
{
    if (!mInit) return;
    GLAutoLock _l(mLock);
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
    OPENGL_CHECK_ERROR;
}

CONTEXT_API void GLProgram::useSingle() const
{
    glUseProgram(mId);
    OPENGL_CHECK_ERROR;
}
void GLProgram::setMatrix(const GLMatrix4& matrix, int id)
{
    float tempMatrix[16];
    matrix.copy(tempMatrix);
    glUniformMatrix4fv(id, 1, GL_FALSE, tempMatrix);
    OPENGL_CHECK_ERROR;
}
void GLProgram::setUniform(int value, int id)
{
    glUniform1i(id, value);
    OPENGL_CHECK_ERROR;
}

void GLProgram::setUniform(float value, int id)
{
    glUniform1f(id, value);
    OPENGL_CHECK_ERROR;
}
void GLProgram::setUniform(float* value, int n, int id)
{
    glUniform1fv(id, n, value);
    OPENGL_CHECK_ERROR;
}
