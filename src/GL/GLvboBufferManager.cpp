//
//  GLvboBufferManager.cpp
//  simple3d
//
//  Created by jiangxiaotang on 15/7/13.
//  Copyright (c) 2015年 jiangxiaotang. All rights reserved.
//

#include <stdio.h>
#include "GL/GLvboBufferManager.h"

GPPtr<GLvboBuffer> GLvboBufferManager::createBasicPos()
{
    const float defaultVex[] = {
        -1.0, -1.0,
        -1.0, 1.0,
        1.0, -1.0,
        1.0, 1.0
    };
    return new GLvboBuffer(defaultVex, 2, 4, GL_TRIANGLE_STRIP);
}

GPPtr<GLvboBuffer> GLvboBufferManager::createBasicTex()
{
    const float defaultTex[] = {
        0.0,0.0,
        0.0,1.0,
        1.0,0.0,
        1.0,1.0
    };
    return new GLvboBuffer(defaultTex, 2, 4, GL_TRIANGLE_STRIP);
}
