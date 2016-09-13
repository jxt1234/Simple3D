//
//  ALFileStream.cpp
//  abs
//
//  Created by jiangxiaotang on 15/7/21.
//  Copyright (c) 2015年 jiangxiaotang. All rights reserved.
//
#include "ALFileStream.h"
#include "utils/GLDebug.h"
#include <stdio.h>
ALFileStream::ALFileStream(const char* name)
{
    mF = fopen(name, "rb");
    GLASSERT(NULL!=mF);
}
ALFileStream::~ALFileStream()
{
    fclose(mF);
}
size_t ALFileStream::vRead(void* buffer, size_t size)
{
    return fread(buffer, 1, size, mF);
}
bool ALFileStream::vIsEnd() const
{
    return feof(mF)!=0;
}


ALWFileStream::ALWFileStream(const char* name)
{
    mF = fopen(name, "wb");
    GLASSERT(NULL!=mF);
}
ALWFileStream::~ALWFileStream()
{
    fclose(mF);
}
size_t ALWFileStream::vWrite(const void* buffer, size_t size)
{
    return fwrite(buffer, 1, size, mF);
}
bool ALWFileStream::vFlush()
{
    return fflush(mF) == 0;
}
