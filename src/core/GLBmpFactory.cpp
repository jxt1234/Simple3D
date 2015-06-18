#include "core/GLBmpFactory.h"
#include <fstream>
#include "utils/debug.h"
GLBmp* GLBmpFactory::createBitmap(const char* file)
{
    std::ifstream input(file);
    GLASSERT(!input.fail());
    return createBitmap(input);
}
GLBmp* GLBmpFactory::createBitmap(std::istream& input)
{
    return NULL;
}
