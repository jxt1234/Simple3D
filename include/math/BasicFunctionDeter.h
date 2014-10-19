#ifndef MATH_BASICFUNCTIONDETER_H
#define MATH_BASICFUNCTIONDETER_H
#include "IFunctionDeter.h"
class BasicFunctionDeter:public IFunctionDeter
{
    public:
        virtual bool vIsFunction(const std::string& name) const;
        virtual bool vComparePriority(const std::string& o1, const std::string& o2) const;
        virtual std::string vDet(const std::string& name) const;
        BasicFunctionDeter();
        virtual ~BasicFunctionDeter();
    private:
        int _findPos(const std::string& name) const;
};
#endif
