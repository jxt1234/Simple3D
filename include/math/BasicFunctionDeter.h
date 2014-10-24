#ifndef MATH_BASICFUNCTIONDETER_H
#define MATH_BASICFUNCTIONDETER_H
#include "IFunctionDeter.h"
#include <map>
#include <istream>
class BasicFunctionDeter:public IFunctionDeter
{
    public:
        struct function
        {
            std::string name;
            int priorty;
            std::string formula;
            std::string detformula;
        };
        virtual bool vIsFunction(const std::string& name) const;
        virtual bool vComparePriority(const std::string& o1, const std::string& o2) const;
        virtual std::string vDet(const std::string& name) const;
        BasicFunctionDeter(std::istream& data);
        virtual ~BasicFunctionDeter();
        virtual void vDivideFormula(const std::string& formula, std::vector<std::string>& result) const;
    private:
        int _findPos(const std::string& name) const;

        std::map<std::string, function> mFunctions;
};
#endif
