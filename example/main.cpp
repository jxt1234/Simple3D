#include "test/GLTest.h"
#include "utils/GP_Clock.h"
#include <sstream>
#include <iostream>
#include "math/FormulaTree.h"
#include "math/BasicFunctionDeter.h"
#include <fstream>
using namespace std;
int main()
{
    std::ifstream is("function.txt");
    BasicFunctionDeter deter(is);
    FormulaTree _test(&deter);
    string x = string("(1.0+v/2.0*cos(u/2.0))*cos(u)");
    string y = string("(1.0+v/2.0*cos(u/2.0))*sin(u)");
    string z = string("v/2.0*sin(u/2.0)");
    _test.setFormula(y);
    _test.expand(std::cout);
    //FormulaTree tree(&deter);
    //tree.setFormula("x*y+p-q*exp(u, v)");
    //tree.expand(std::cout);

    //string s("u");
    //GPPtr<FormulaTree> detTree = tree.detByName(s);
    //detTree->expand(std::cout);
    return 1;
}
