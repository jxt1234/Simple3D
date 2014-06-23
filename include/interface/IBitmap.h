#ifndef INTERFACE_IBITMAP_H
#define INTERFACE_IBITMAP_H
#include <stdlib.h>
#include <assert.h>
#include "GLColor.h"
class IBitmap
{
    public:
        IBitmap():mWidth(0), mHeight(0){}
        virtual ~IBitmap(){}
        virtual GLColor getColor(int x, int y)=0;
        virtual void setColor(const GLColor& c, int x, int y) = 0;

        inline int getWidth() const{return mWidth;}
        inline int getHeight() const{return mHeight;}
        /*Must Ensure there has enough memory for the dst*/
        static void copy(IBitmap* src, IBitmap* dst)
        {
            assert(src->mWidth == dst->mWidth);
            assert(src->mHeight == dst->mHeight);
            for (int i=0; i<src->mWidth; ++i)
            {
                for (int j=0; j<src->mHeight; ++j)
                {
                    GLColor c = src->getColor(i, j);
                    dst->setColor(c, i, j);
                }
            }
        }
        virtual void clear(GLColor c)
        {
            for (int i=0; i<mWidth; ++i)
            {
                for (int j=0; j<mHeight; ++j)
                {
                    this->setColor(c, i, j);
                }
            }
        }
    protected:
        int mWidth;
        int mHeight;
};


#endif
