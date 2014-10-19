#include "math/BasicFunctionDeter.h"
static const char* gOperator[] = {
"+",
"-",
"*",
"/",
"exp",
"cos",
"sin",
"tan",
"pow"
};

static int gSize = sizeof(gOperator)/sizeof(const char*);

BasicFunctionDeter::BasicFunctionDeter()
{
}

BasicFunctionDeter::~BasicFunctionDeter()
{
}
bool BasicFunctionDeter::vIsFunction(const std::string& name) const
{
    if (_findPos(name) == -1)
    {
        return false;
    }
    return true;
}
bool BasicFunctionDeter::vComparePriority(const std::string& o1, const std::string& o2) const
{
    int p1 = _findPos(o1);
    int p2 = _findPos(o2);
    return p1>p2;
}
int BasicFunctionDeter::_findPos(const std::string& name) const
{
    for (int i=0; i<gSize; ++i)
    {
        if (name == gOperator[i])
        {
            return i;
        }
    }
    return -1;
}
std::string BasicFunctionDeter::vDet(const std::string& name) const
{
    //TODO
    std::string t;
    return t;
}
