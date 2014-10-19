#ifndef MATH_IFUNCTIONDETER_H
#define MATH_IFUNCTIONDETER_H
#include <string>
class IFunctionDeter
{
    public:
        enum
        {
            NUM = 0,
            OPERATOR = 1,
            BRACEL_L = 2,
            BRACEL_R = 3,
            UNKNOWN = 4
        };
        virtual bool vIsFunction(const std::string& name) const = 0;
        /*Return true if o1's priority is larger than o2*/
        virtual bool vComparePriority(const std::string& o1, const std::string& o2) const = 0;
        virtual std::string vDet(const std::string& name) const = 0;
        int type(const std::string& word) const
        {
            if (word == "(")
            {
                return BRACEL_L;
            }
            if (word == ")")
            {
                return BRACEL_R;
            }
            if (this->vIsFunction(word))
            {
                return OPERATOR;
            }
            return NUM;
        }
        IFunctionDeter(){}
        virtual ~IFunctionDeter(){}
};
#endif
