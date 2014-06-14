#include "display/program.h"
#include <assert.h>
#include <sstream>
#include <fstream>
using namespace std;

program::program()
{
    mId = 0;
    mInit = false; 
    mVertex = NULL;
    mFragment = NULL;
}

void program::load(const std::string& vertex, const std::string& frag)
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

static void loadAllContent(const char* file, char* &c)
{
    ifstream is(file);
    is.seekg(0, ios::end);
    int length = is.tellg();
    is.seekg(0, ios::beg);
    c = new char[length+1];
    is.read(c, length);
    is.close();
}

void program::loadFiles(const char* vertex, const char* frag)
{
    assert(NULL!=vertex);
    assert(NULL!=frag);
    if (mVertex) delete [] mVertex;
    if (mFragment) delete [] mFragment;
    mInit = false;
    loadAllContent(vertex, mVertex);
    loadAllContent(frag, mFragment);
}

program::program(const std::string& vertex, const std::string& frag)
{
    mInit = false;
    mId = 0;
    load(vertex, frag);
}

program::~program()
{
    ///*If the program is not destory before, it shouldn't be freed*/
    //assert(!mInit);
    if (mVertex) delete [] mVertex;
    if (mFragment) delete [] mFragment;
}
