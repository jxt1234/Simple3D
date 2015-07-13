//
//  IGLDrawWork.cpp
//  simple3d
//
//  Created by jiangxiaotang on 15/7/13.
//  Copyright (c) 2015年 jiangxiaotang. All rights reserved.
//

#include <stdio.h>
#include "GL/IGLDrawWork.h"

void IGLDrawWork::drawSingle(GLTexture* src, GLvboBuffer* vs, GLvboBuffer* ts)
{
    this->onDraw(&src, 1, vs, ts);
}

