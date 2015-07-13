//
//  GLvboBufferManager.h
//  simple3d
//
//  Created by jiangxiaotang on 15/7/13.
//  Copyright (c) 2015年 jiangxiaotang. All rights reserved.
//

#ifndef simple3d_GLvboBufferManager_h
#define simple3d_GLvboBufferManager_h
#include "GLvboBuffer.h"
class GLvboBufferManager
{
public:
    static GPPtr<GLvboBuffer> createBasicPos();
    static GPPtr<GLvboBuffer> createBasicTex();
private:
};

#endif
