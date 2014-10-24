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
    _test.setFormula("d0+d1");
    _test.expand(std::cout);
    FormulaTree tree(&deter);
    tree.setFormula("x*y+p-q*exp(u, v)");
    tree.expand(std::cout);

    string s("u");
    GPPtr<FormulaTree> detTree = tree.detByName(s);
    detTree->print(std::cout);
    detTree->expand(std::cout);
    return 1;
}
