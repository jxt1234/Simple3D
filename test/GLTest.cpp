#include "test/GLTest.h"
#include "utils/GLDebug.h"
#include <stdlib.h>

GLTestSuit* GLTestSuit::global = NULL;

GLTestSuit* GLTestSuit::get()
{
    if (global ==NULL) global = new GLTestSuit;
    return global;
}

GLTestSuit::~GLTestSuit()
{
    for (int i=0; i<mTests.size(); ++i)
    {
        delete mTests[i];
    }
    mTests.clear();
}

void GLTestSuit::insert(GLTest* t, const char* name)
{
    t->name = name;
    mTests.push_back(t);
}

void GLTestSuit::run()
{
    GLTestSuit::get();
    for (int i=0; i < (global->mTests).size();++i)
    {
        GLTest* t = (global->mTests[i]);
        FUNC_PRINT_ALL((t->name).c_str(), s);
        int start = clock();
        t->run();
        int end = clock();
        FUNC_PRINT((end-start));
    }
}
