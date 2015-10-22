#include "test/GLTest.h"
#include "utils/GP_Clock.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "core/GLBmp.h"
#include "core/GLBitmapFactory.h"
using namespace std;
int main()
{
    GPPtr<GLBmp> src = new GLBmp(512, 512);
    for (int i=0; i<512; ++i)
    {
        for (int j=0; j<512; ++j)
        {
            auto _p = src->getAddr(j, 512-i-1);
            _p[3] = 255;
            _p[0] = (j%64)*4;
            _p[1] = (i%64)*4;
            _p[2] = (i/64)*32 + (j/64)*4;
        }
    }
    GLBitmapFactory::dump(src.get(), "filter_standard.png");
}
