//
//  GLColorMap.cpp
//  simple3d
//
//  Created by jiangxiaotang on 15/10/10.
//  Copyright (c) 2015年 jiangxiaotang. All rights reserved.
//

#include "transform/GLColorMap.h"
#include "utils/debug.h"
#include "utils/GP_Clock.h"
GLBmp* GLColorMap(GLBmp* src, GLColorTable* table)
{
    GLASSERT(NULL!=src);
    GLBmp* dst = new GLBmp(src->width(), src->height());
    GLColorMapInner(dst, src, table);
    return dst;
}
void GLColorMapInner(GLBmp* dst, const GLBmp* src, const GLBmp* table)
{
    //GPCLOCK;
    GLASSERT(NULL!=dst);
    GLASSERT(NULL!=src);
    GLASSERT(NULL!=table);
    GLASSERT(dst->width() == src->width());
    GLASSERT(dst->height() == src->height());
    GLASSERT(1 == table->height());
    GLASSERT(256 == table->width());
    auto w = dst->width();
    auto h = dst->height();
    auto bpp = table->bpp();
    auto _table = table->getAddr(0, 0);
    for (int y=0; y<h; ++y)
    {
        auto _dst_line = dst->getAddr(0, y);
        auto _src_line = src->getAddr(0, y);
        for (int x=0; x<w; ++x)
        {
            auto _dst = _dst_line + bpp*x;
            auto _src = _src_line + bpp*x;
            _dst[0] = _table[bpp*_src[0]+0];
            _dst[1] = _table[bpp*_src[1]+1];
            _dst[2] = _table[bpp*_src[2]+2];
            _dst[3] = _src[3];
        }
    }
}
