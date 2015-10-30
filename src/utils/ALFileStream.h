#ifndef SRC_UTILS_ALFILESTREAM_H
#define SRC_UTILS_ALFILESTREAM_H
//
//  ALFileStream.h
//  abs
//
//  Created by jiangxiaotang on 15/7/21.
//  Copyright (c) 2015年 jiangxiaotang. All rights reserved.
//
#include "utils/ALStream.h"
#include <stdio.h>
class ALFileStream:public ALStream
{
public:
    ALFileStream(const char* name);
    virtual ~ALFileStream();
    virtual size_t vRead(void* buffer, size_t size);
    virtual bool vIsEnd() const;
private:
    FILE* mF;
};
class ALWFileStream:public ALWStream
{
public:
    ALWFileStream(const char* name);
    virtual size_t vWrite(const void* buffer, size_t size);
    virtual bool vFlush();
    virtual ~ALWFileStream();
private:
    FILE* mF;
};
#endif
