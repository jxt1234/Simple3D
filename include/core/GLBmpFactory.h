#ifndef CORE_GLBMPFACTORY_H
#define CORE_GLBMPFACTORY_H
#include <istream>
#include "GLBmp.h"
class GLBmpFactory
{
public:
    static GLBmp* createBitmap(const char* file);
    static GLBmp* createBitmap(std::istream& input);
};
#endif
