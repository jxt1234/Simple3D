#include "GL/GLProgram.h"
#include <assert.h>
#include <sstream>
#include <fstream>
#include <string.h>
using namespace std;

GLProgram::GLProgram()
{
    mId = 0;
    mInit = false; 
    mVertex = NULL;
    mFragment = NULL;
}

void GLProgram::load(const std::string& vertex, const std::string& frag)
{
    mInit = false;
    if (mVertex) delete [] mVertex;
    if (mFragment) delete [] mFragment;
    mVertex = new char[vertex.size()+1];
    vertex.copy(mVertex, vertex.size(), 0);
    mVertex[vertex.size()] = 0;
    mFragment = new char[frag.size()+1];
    frag.copy(mFragment, frag.size(), 0);
    mFragment[frag.size()] = 0;
}

void GLProgram::load(const char* vex, const char* frag)
{
    assert(NULL!=vex);
    assert(NULL!=frag);
#define COPYS(dst, src)\
    {\
        if (dst) delete [] dst;\
        int n = strlen(src);\
        dst = new char[n+1];\
        memcpy(dst, src, n);\
        dst[n] = '\0';\
    }

    COPYS(mVertex, vex);
    COPYS(mFragment, frag);
#undef COPYS
}

static void loadAllContent(const char* file, char* &c)
{
    ifstream is(file);
    is.seekg(0, ios::end);
    int length = is.tellg();
    is.seekg(0, ios::beg);
    c = new char[length+1];
    is.read(c, length);
    c[length] = '\0';
    is.close();
}

void GLProgram::loadFiles(const char* vertex, const char* frag)
{
    assert(NULL!=vertex);
    assert(NULL!=frag);
    if (mVertex) delete [] mVertex;
    if (mFragment) delete [] mFragment;
    mInit = false;
    loadAllContent(vertex, mVertex);
    loadAllContent(frag, mFragment);
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
    //assert(!mInit);
    if (mVertex) delete [] mVertex;
    if (mFragment) delete [] mFragment;
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
    bool res = compileShader(vert);
    assert(true == res);
    res = (compileShader(frag));
    assert(true == res);
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

CONTEXT_API int GLProgram::attr(const char* name) const
{
    assert(NULL!=name && 0!=mId);
    return glGetAttribLocation(mId, name);
}
CONTEXT_API int GLProgram::uniform(const char* name) const
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
