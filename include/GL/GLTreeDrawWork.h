//
//  GLTreeDrawWork.h
//  simple3d
//
//  Created by jiangxiaotang on 15/7/13.
//  Copyright (c) 2015年 jiangxiaotang. All rights reserved.
//

#ifndef simple3d_GLTreeDrawWork_h
#define simple3d_GLTreeDrawWork_h
#include "IGLDrawWork.h"
class GLTreeDrawWork:public IGLDrawWork
{
public:
    GLTreeDrawWork(GPPtr<IGLDrawWork> basic):mBasic(basic){}
    virtual ~GLTreeDrawWork(){}
    void addNode(GPPtr<GLTreeDrawWork> node)
    {
        mChildren.push_back(node);
    }
    virtual void onDraw(GLTexture** src, int n, GLvboBuffer* vs, GLvboBuffer* ts);
    virtual size_t vMap(double* parameters, size_t n) {return 0;}
private:
    std::vector<GPPtr<GLTreeDrawWork> > mChildren;
    GPPtr<IGLDrawWork> mBasic;
};

#endif
