//
//  GLAutoStorage.h
//  simple3d
//
//  Created by jiangxiaotang on 15/7/13.
//  Copyright (c) 2015年 jiangxiaotang. All rights reserved.
//

#ifndef simple3d_GLAutoStorage_h
#define simple3d_GLAutoStorage_h
template<typename T>
class GLAutoStorage
{
public:
    GLAutoStorage(size_t size)
    {
        m = new T[size];
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
