#include "test/GLTest.h"
#include "utils/GP_Clock.h"
#include <sstream>
#include <iostream>
#include "math/FormulaTree.h"
#include "math/BasicFunctionDeter.h"
int main()
{
    BasicFunctionDeter deter;
    FormulaTree tree(&deter);
    tree.setFormula("x*y+p-q*exp(u, v)");
    tree.print(std::cout);
    return 1;
}
