#include "display/program.h"
#include <assert.h>
#include <sstream>
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
    mVertex = new char[vertex.size()+1];
    vertex.copy(mVertex, vertex.size(), 0);
    mVertex[vertex.size()] = 0;
    mFragment = new char[frag.size()+1];
    frag.copy(mFragment, frag.size(), 0);
    mFragment[frag.size()] = 0;
}
program::program(const std::string& vertex, const std::string& frag)
{
    mInit = false;
    mId = 0;
    load(vertex, frag);
}

program::~program()
{
    /*If the program is not destory before, it shouldn't be freed*/
    assert(!mInit);
    if (mVertex) delete [] mVertex;
    if (mFragment) delete [] mFragment;
}
