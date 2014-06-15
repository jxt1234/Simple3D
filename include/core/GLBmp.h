#ifndef CORE_GLBMP_H
#define CORE_GLBMP_H

#include <stdlib.h>
#include <stdint.h>
#include "interface/IBitmap.h"
#include <FreeImage.h>

/*Only one color format ARGB*/
class GLBmp:public IBitmap
{
    public:
        GLBmp(){mBitmap = NULL, mWidth = 0, mHeight = 0;}
        GLBmp(int w, int h);
        GLBmp(const char* pic){loadPicture(pic);}
        void loadPicture(const char* pic);
        void save(const char* path);
        void* pixels() const;
        //
        virtual ~GLBmp();
        virtual GLColor getColor(int x, int y);
        virtual void setColor(const GLColor& c, int x, int y);
    protected:
        FIBITMAP* mBitmap;
};


#endif
