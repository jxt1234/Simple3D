#ifndef CORE_GLBITMAPFACTORY_H
#define CORE_GLBITMAPFACTORY_H
#include "GLBmp.h"
class GLBitmapFactory
{
    public:
        static GLBmp* create(const char* filename);
        static GLBmp* create(unsigned char* data, int length);
        static void dump(const GLBmp* bmp, const char* filename);
};
#endif
