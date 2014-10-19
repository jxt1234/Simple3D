/******************************************************************
   Copyright 2014, Jiang Xiao-tang

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
******************************************************************/
#ifndef MATH_FORMULATREE_H
#define MATH_FORMULATREE_H
#include "utils/RefCount.h"
#include "AbstractPoint.h"
#include "IFunctionDeter.h"


class FormulaTreePoint:public AbstractPoint
{
    public:
        FormulaTreePoint();
        virtual ~FormulaTreePoint();
        friend class FormulaTree;
        inline const std::string& name() const {return mName;}
        inline int type() const {return mT;}
        static int findRoot(const std::vector<std::string>& simbols, const std::vector<int>& types, int sta, int fin, const IFunctionDeter* basic);
        static void divideWords(const std::vector<int>& types, 
                int sta, int mid, int fin,
                std::vector<int>& starts, std::vector<int>& ends);
        void createFrom(const std::vector<std::string>& simbols, const std::vector<int>& types, const IFunctionDeter* basic);
    protected:
        virtual void printBefore(std::ostream& out);
        virtual void printAfter(std::ostream& out);
    private:
        void _createFrom(const std::vector<std::string>& simbols, const std::vector<int>& types,
                int sta, int fin, const IFunctionDeter* basic);
        int mT;
        std::string mName;
};
class FormulaTree:public RefCount
{
    public:
        FormulaTree(const IFunctionDeter* basic);
        virtual ~FormulaTree();
        void setFormula(const std::string& formula);
        void expand(std::ostream& output);
        inline FormulaTreePoint* root() {return mRoot;}
        void print(std::ostream& s);
        inline bool isvalid() const {return mValid;}
        static void divideFormula(std::vector<std::string>& results, const std::string& formula);
        bool valid(const std::vector<int>& words) const;
    private:
        FormulaTreePoint* mRoot;
        const IFunctionDeter* mBasic;
        bool mValid;
};
#endif
