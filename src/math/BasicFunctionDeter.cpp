#include "math/BasicFunctionDeter.h"
#include "utils/debug.h"

BasicFunctionDeter::BasicFunctionDeter(std::istream& data)
{
    function f;
    data >> f.name;
    do
    {
        data >> f.priorty;
        data >> f.formula;
        data >> f.detformula;
        mFunctions.insert(std::make_pair(f.name, f));
    }while (data >> f.name);
}

BasicFunctionDeter::~BasicFunctionDeter()
{
}
void BasicFunctionDeter::vDivideFormula(const std::string& formula, std::vector<std::string>& results) const
{
    int sta = 0;
    int fin = 0;
    bool startWords = false;
#define FINISHWORDS(i)\
                if (startWords)\
                {\
                    fin = i;\
                    startWords = false;\
                    std::string _str;\
                    _str.assign(formula, sta, fin-sta);\
                    results.push_back(_str);\
                }

    for (int i=0;i<formula.size(); ++i)
    {
        char c = formula.at(i);
        if ('['==c||'{'==c) c='(';
        if (']'==c||'}'==c) c=')';
        switch (c)
        {
            case ' ':
            case '\t':
            case '\n':
            case ',':
                FINISHWORDS(i);
                break;
            case '*':
            case '+':
            case '-':
            case '/':
            case '(':
            case ')':
                FINISHWORDS(i);
                {
                    std::string _str;
                    _str.push_back(c);
                    results.push_back(_str);
                }
                break;
            default:
                if (!startWords)
                {
                    startWords = true;
                    sta = i;
                }
                break;
        }
    }
    FINISHWORDS((formula.size()));
#undef FINISHWORDS
}

bool BasicFunctionDeter::vIsFunction(const std::string& name) const
{
    if (mFunctions.find(name)!=mFunctions.end())
    {
        return true;
    }
    return false;
}
bool BasicFunctionDeter::vComparePriority(const std::string& o1, const std::string& o2) const
{
    std::map<std::string, function>::const_iterator p1, p2;
    p1 = mFunctions.find(o1);
    p2 = mFunctions.find(o2);
    return (p1->second).priorty > (p2->second).priorty;
}
std::string BasicFunctionDeter::vDet(const std::string& name) const
{
    std::map<std::string, function>::const_iterator p1 = mFunctions.find(name);
    return (p1->second).detformula;
}
