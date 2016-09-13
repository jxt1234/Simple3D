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
#include <sstream>
#include "math/FormulaTree.h"
#include "utils/GLDebug.h"
#include <iostream>
//#define F_DEBUG
class FormulaTreePointCopy:public AbstractPoint::IPointCopy
{
    public:
        virtual AbstractPoint* copy(AbstractPoint* src)
        {
            FormulaTreePoint* p = (FormulaTreePoint*)src;
            FormulaTreePoint* _res = new FormulaTreePoint;
            _res->mT = p->mT;
            _res->mName = p->mName;
            return _res;
        }
};

FormulaTreePoint::FormulaTreePoint()
{
}
FormulaTreePoint::~FormulaTreePoint()
{
}
void FormulaTreePoint::createFrom(const std::string& formula, const IFunctionDeter* basic)
{
    GLASSERT(NULL!=basic);
    std::vector<std::string> simbols;
    basic->vDivideFormula(formula, simbols);
    std::vector<int> types;
    types.reserve(simbols.size());
    for (int i=0; i<simbols.size(); ++i)
    {
        types.push_back(basic->type(simbols.at(i)));
    }
    createFrom(simbols, types, basic);
}
void FormulaTreePoint::_replaceByTable(const std::map<std::string, FormulaTreePoint*>& tables)
{
    GLASSERT(mT == IFunctionDeter::OPERATOR);
    typedef std::map<std::string, FormulaTreePoint*>::const_iterator ITER;
    FormulaTreePointCopy copy;
    for (int i=0; i<mChildren.size(); ++i)
    {
        FormulaTreePoint* cp = (FormulaTreePoint*)(mChildren.at(i));
        if (cp->mT == IFunctionDeter::OPERATOR)
        {
            cp->_replaceByTable(tables);
            continue;
        }
        GLASSERT(cp->mT == IFunctionDeter::NUM);
        ITER it = tables.find(cp->mName);
        if (it==tables.end())
        {
            continue;
        }
        GLASSERT(it!=tables.end());
        FormulaTreePoint* rep = it->second;
        AbstractPoint* rep_copy = AbstractPoint::deepCopy(rep, &copy);
        GLASSERT(NULL!=rep_copy);
        cp->decRef();
        mChildren[i] = rep_copy;
    }
}
FormulaTreePoint* FormulaTreePoint::detByName(const std::string& name, const IFunctionDeter* basic) const
{
    GLASSERT(NULL!=basic);
    GLASSERT(mT == IFunctionDeter::NUM || mT == IFunctionDeter::OPERATOR);
    FormulaTreePoint* res = new FormulaTreePoint;
    res->mT = mT;
    if (mT == IFunctionDeter::NUM)
    {
        if (mName == name)
        {
            res->mName = "1.0";
        }
        else
        {
            res->mName = "0.0";
        }
        return res;
    }
    std::string formula = basic->vDet(mName);
    res->createFrom(formula, basic);

    std::vector<AbstractPoint*> cleanPoints;//The points created by detByName() method must be cleaned
    /*Create replace table*/
    /*d0-det_points[0], d1-det_points[1], x0-mChildren[0], and so on*/
    std::map<std::string, FormulaTreePoint*> replaceTable;
    for (int i=0; i<mChildren.size(); ++i)
    {
        std::ostringstream raw_name;
        std::ostringstream det_name;
        raw_name << "x"<<i;
        det_name << "d"<<i;
        FormulaTreePoint* p = (FormulaTreePoint*)(mChildren.at(i));
        FormulaTreePoint* dp = p->detByName(name, basic);
        cleanPoints.push_back(dp);

        replaceTable.insert(std::make_pair(raw_name.str(), p));
        replaceTable.insert(std::make_pair(det_name.str(), dp));
    }
    res->_replaceByTable(replaceTable);
    for (int i=0; i<cleanPoints.size(); ++i)
    {
        (cleanPoints.at(i))->decRef();
    }
    return res;
}
void FormulaTreePoint::_expandUnit(std::ostream& output, const IFunctionDeter* basic) const
{
    GLASSERT(NULL!=basic);
    if (!basic->vIsFunction(mName))
    {
        output<<mName;
        GLASSERT(mChildren.empty());
        return;
    }
    /*TODO use formula string*/
    if (mName=="+" || mName == "-" || mName == "*" || mName=="/")
    {
        FormulaTreePoint* p1 = (FormulaTreePoint*)mChildren[0];
        FormulaTreePoint* p2 = (FormulaTreePoint*)mChildren[1];
        output <<"(";
        p1->_expandUnit(output, basic);
        output << mName;
        p2->_expandUnit(output, basic);
        output <<")";
        return;
    }
    output<<mName;
    output << "(";
    for (int i=0; i<mChildren.size(); ++i)
    {
        FormulaTreePoint* p = (FormulaTreePoint*)(mChildren.at(i));
        p->_expandUnit(output, basic);
        if (i!=mChildren.size()-1)

        {
            output << ",";
        }
    }
    output << ")";
}

void FormulaTreePoint::printBefore(std::ostream& out)
{
    out << "<"<<mName<<">\n";
    out << "<Type>"<<mT<<"</Type>\n";
}
void FormulaTreePoint::printAfter(std::ostream& out)
{
    out << "</"<<mName<<">\n";
}
void FormulaTreePoint::divideWords(const std::vector<int>& types, 
        int sta, int mid, int fin, std::vector<int>& starts, std::vector<int>& ends)
{
    GLASSERT(sta<=mid && mid<fin && fin<types.size());
    GLASSERT(IFunctionDeter::OPERATOR == types[mid]);
    int ssta = sta;
    for (;ssta <= mid && types[ssta]==IFunctionDeter::BRACEL_L; ssta++);
    if (ssta != mid)//This means mid is binocular Operator
    {
        starts.push_back(sta);ends.push_back(mid-1);
        starts.push_back(mid+1);ends.push_back(fin);
        return;
    }
    GLASSERT(types[mid+1] == IFunctionDeter::BRACEL_L);
    GLASSERT(types[fin] == IFunctionDeter::BRACEL_R);
    GLASSERT(mid+2<=fin-1);
    int _sta = mid+2;
    int _fin = fin-1;
    //TODO Support multi cular Operator, currently we only support:f(x)
    //std::cout << mid+2 << ", " <<fin<<"\n";
    for (; _sta<_fin; ++_sta, --_fin)
    {
        if (IFunctionDeter::BRACEL_L!=types[_sta])
        {
            break;
        }
    }
    starts.push_back(_sta);
    ends.push_back(_fin);
}

int FormulaTreePoint::findRoot(const std::vector<std::string>& simbols, const std::vector<int>& types, int sta, int fin, const IFunctionDeter* basic)
{
    GLASSERT(simbols.size() == types.size());
    //for (int i=sta; i<=fin; ++i)
    //{
    //    printf("%s ", simbols[i].c_str());
    //}
    //printf("\n");
    /*The root operator is the latest one to compute*/
    int root = sta;
    int rootType = IFunctionDeter::UNKNOWN;
    std::string rootOperator;
    for (int i=sta; i<=fin; ++i)
    {
        if (types[i] < IFunctionDeter::BRACEL_L)
        {
            rootType = types[i];
            rootOperator = simbols[i];
            root = i;
        }
        if (rootType == IFunctionDeter::OPERATOR)
        {
            break;
        }
    }
    GLASSERT(rootType == IFunctionDeter::NUM || rootType == IFunctionDeter::OPERATOR);
    if (rootType == IFunctionDeter::NUM)
    {
        return root;
    }
    int depth = 0;
    int rootDepth = 1000;//FIXME
    root = sta;
    rootType = IFunctionDeter::NUM;
    /*Find latest operator*/
    for (int i=root; i<=fin; ++i)
    {
        switch (types[i])
        {
            case IFunctionDeter::BRACEL_L:
                depth++;
                break;
            case IFunctionDeter::BRACEL_R:
                depth--;
                break;
            case IFunctionDeter::OPERATOR:
                if (rootDepth>depth)
                {
                    root = i;
                    rootOperator = simbols[i];
                    rootDepth = depth;
                    rootType = types[i];
                }
                else if (rootDepth == depth)
                {
                    std::string current = simbols[i];
                    //root operator will be compute earlier than current, so set current be root
                    if (rootType == IFunctionDeter::NUM)
                    {
                        rootType = IFunctionDeter::OPERATOR;
                        root = i;
                        rootOperator = current;
                    }
                    else if (!basic->vComparePriority(current, rootOperator))
                    {
                        rootOperator = current;
                        root = i;
                    }
                }
                break;
            default:
                break;
        }
    }
    return root;
}

void FormulaTreePoint::createFrom(const std::vector<std::string>& simbols, const std::vector<int>& types, const IFunctionDeter* basic)
{
    _createFrom(simbols, types, 0, types.size()-1, basic);
}
void FormulaTreePoint::_createFrom(const std::vector<std::string>& simbols, const std::vector<int>& types, int sta, int fin, const IFunctionDeter* basic)
{
    GLASSERT(sta>=0&&sta<=fin);
    GLASSERT(fin<simbols.size());
    GLASSERT(types.size() == simbols.size());
    int root = findRoot(simbols, types, sta, fin, basic);
    mName = simbols[root];
    mT = types[root];
    if (mT!=IFunctionDeter::OPERATOR)
    {
        return;
    }
    /*Divide*/
    std::vector<int> starts;
    std::vector<int> ends;
    divideWords(types, sta, root, fin, starts, ends);
    GLASSERT(starts.size() == ends.size());
    for (int i=0; i<starts.size(); ++i)
    {
        FormulaTreePoint* p = new FormulaTreePoint;
        int newSta = starts[i];
        int newFin = ends[i];
        p->_createFrom(simbols, types, newSta, newFin, basic);
        addPoint(p);
    }
}

FormulaTree::FormulaTree(const IFunctionDeter* deter)
{
    mRoot = NULL;
    mValid = false;
    mBasic = deter;
}
FormulaTree::FormulaTree(const IFunctionDeter* deter, const std::string& formula)
{
    mRoot = NULL;
    mValid = false;
    mBasic = deter;

    this->setFormula(formula);
}
FormulaTree::~FormulaTree()
{
    SAFE_UNREF(mRoot);
}
void FormulaTree::setFormula(const std::string& formula)
{
#ifdef F_DEBUG
    std::cout << formula <<"\n";
#endif
    GLASSERT(NULL!=mBasic);
    SAFE_UNREF(mRoot);
    std::vector<std::string> words;
    mBasic->vDivideFormula(formula, words);
    GLASSERT(!words.empty());
    std::vector<int> types;
    types.reserve(words.size());
    for (int i=0; i<words.size(); ++i)
    {
        types.push_back(mBasic->type(words[i]));
#ifdef F_DEBUG
        std::cout << types[i] << " ";
#endif
    }
#ifdef F_DEBUG
    std::cout << "\n";
#endif
    mValid = valid(types);
    GLASSERT(true == mValid);
    if (!mValid) return;
    mRoot = new FormulaTreePoint;
    mRoot->createFrom(words, types, mBasic);
}

void FormulaTree::print(std::ostream& s)
{
    GLASSERT(NULL!=mRoot);
    mRoot->print(s);
}

FormulaTree* FormulaTree::detByName(const std::string& name) const
{
    FormulaTree* tree = new FormulaTree(mBasic);
    tree->mValid = true;
    tree->mRoot = mRoot->detByName(name, mBasic);
    return tree;
}
void FormulaTree::expand(std::ostream& output) const
{
    GLASSERT(mRoot!=NULL);
    mRoot->_expandUnit(output, mBasic);
}
bool FormulaTree::valid(const std::vector<int>& words) const
{
    GLASSERT(NULL!=mBasic);
    int depth=0;
    int preType = IFunctionDeter::UNKNOWN;
    for (int i=0; i<words.size(); ++i)
    {
        int type = words[i];
        switch (type)
        {
            case IFunctionDeter::BRACEL_L:
                depth++;
                break;
            case IFunctionDeter::BRACEL_R:
                if (preType == IFunctionDeter::OPERATOR)
                {
                    FUNC_PRINT(preType);
                    GLASSERT(false);
                    return false;
                }
                depth--;
                break;
            default:
                break;
        }
        preType = type;
    }
    return (0 == depth);
}


