//
//  GLTreeDrawWork.cpp
//  simple3d
//
//  Created by jiangxiaotang on 15/7/13.
//  Copyright (c) 2015年 jiangxiaotang. All rights reserved.
//

#include <stdio.h>
#include "GL/GLTreeDrawWork.h"
#include "GL/GLvboBufferManager.h"
#include "GL/GLAutoFbo.h"

void GLTreeDrawWork::onDraw(GLTexture** src, int n, GLvboBuffer* vs, GLvboBuffer* ts)
{
    GLASSERT(NULL!=src);
    GLASSERT(1 == n);
    GLASSERT(NULL!=vs);
    GLASSERT(NULL!=ts);
    GLASSERT(NULL!=src[0]);
    if (mChildren.size() == 0)
    {
        mBasic->onDraw(src, 1, vs, ts);
        return;
    }
    GPPtr<GLvboBuffer> mVs = GLvboBufferManager::createBasicPos();
    GPPtr<GLvboBuffer> mTs = GLvboBufferManager::createBasicTex();
    std::vector<GPPtr<GLTexture> > textures;
    for (int i=0; i<mChildren.size(); ++i)
    {
        if (mChildren[i].get() == NULL)
        {
            textures.push_back(NULL);
            continue;
        }
        GLTexture* dst = new GLTexture;
        textures.push_back(dst);
        dst->upload(NULL, src[0]->width(), src[0]->height());
        GLAutoFbo __fbo(*dst);
        mChildren[i]->onDraw(src, 1, mVs.get(), mTs.get());
    }
    GLTexture** srcs = new GLTexture*[mChildren.size()];
    for (int i=0; i<textures.size(); ++i)
    {
        srcs[i] = textures[i].get();
        if (NULL == srcs[i])
        {
            srcs[i] = src[0];
        }
    }
    mBasic->onDraw(srcs, (int)mChildren.size(), vs, ts);
    delete [] srcs;
}
