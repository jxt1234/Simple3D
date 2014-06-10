#ifndef FRAGMENT_GL_FRAGTEXCORD_H
#define FRAGMENT_GL_FRAGTEXCORD_H
#include "GLAbstractRasterizatedVarying.h"
#include <vector>
class GL_FragTexcord:public GLAbstractRasterizatedVarying
{
    public:
        //For output
        std::vector<int> loadInt(int n)
        {
            std::vector<int> result;
            int x = mData[n][0]*w;
            int y = mData[n][1]*h;
            if (x>=w) x = w-1;
            if (y>=h) y = h-1;
            result.push_back(x);
            result.push_back(y);
            return result;
        }
        //Basic
        GL_FragTexcord(int _w, int _h):w(_w), h(_h), GLAbstractRasterizatedVarying(2){}
        virtual ~GL_FragTexcord(){}
    protected:
        int w;
        int h;
};

#endif
