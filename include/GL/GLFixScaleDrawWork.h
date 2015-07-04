//
//  GLFixScaleDrawWork.h
//  simple3d
//
//  Created by jiangxiaotang on 15/7/4.
//  Copyright (c) 2015年 jiangxiaotang. All rights reserved.
//

#ifndef simple3d_GLFixScaleDrawWork_h
#define simple3d_GLFixScaleDrawWork_h
#include "IGLDrawWork.h"
#include "GLTexture.h"
#include "GLAutoFbo.h"
#include "GLvboBuffer.h"
#include "GLProgram.h"
class GLFixScaleDrawWork:public IGLDrawWork
{
public:
    GLFixScaleDrawWork(GPPtr<IGLDrawWork> origin, int w, int h);
    virtual ~GLFixScaleDrawWork();
    virtual void onDraw(GLTexture* src, GLvboBuffer* vs, GLvboBuffer* ts);
    virtual int vMap(double* parameters, int n);

private:
    GPPtr<IGLDrawWork> mWork;
    GPPtr<GLTexture> mTexture;
    GPPtr<GLvboBuffer> mVs;
    GPPtr<GLvboBuffer> mTs;
    GPPtr<GLProgram> mProgram;
};

#endif
