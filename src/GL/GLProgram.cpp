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
        int n = strlen(vex);\
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
