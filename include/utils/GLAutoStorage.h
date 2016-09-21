#ifndef UTILS_GLAUTOSTORAGE_H
#define UTILS_GLAUTOSTORAGE_H
#include "GLDebug.h"
//
//  GLAutoStorage.h
//  simple3d
//
//  Created by jiangxiaotang on 15/7/13.
//  Copyright (c) 2015年 jiangxiaotang. All rights reserved.
//
template<typename T>
class GLAutoStorage
{
public:
    GLAutoStorage(size_t size)
    {
        m = new T[size];
        GLASSERT(NULL!=m);
    }
    ~GLAutoStorage()
    {
        delete [] m;
    }
    T* get() const {return m;}
private:
    T* m;
};
#define GLAUTOSTORAGE(x, type, size) GLAutoStorage<type> __##x(size); type * x = __##x.get();
#endif
