#ifndef INCLUDE_UTILS_ALSTREAM_H
#define INCLUDE_UTILS_ALSTREAM_H
//
//  ALStream.h
//  abs
//
//  Created by jiangxiaotang on 15/7/21.
//  Copyright (c) 2015年 jiangxiaotang. All rights reserved.
//
#include "RefCount.h"
class ALStream : public RefCount
{
public:
    /*If the buffer is NULL, it means skip size bytes, return the fact bytes it read*/
    virtual size_t vRead(void* buffer, size_t size) = 0;
    
    /*Return true if the stream has moved to end*/
    virtual bool vIsEnd() const = 0;
    
    template <typename T>
    T read()
    {
        T buffer;
        this->vRead(&buffer, sizeof(T));
        return buffer;
    }
protected:
    ALStream() = default;
    virtual ~ALStream() = default;
private:
    ALStream(const ALStream& stream) = default;
    ALStream& operator=(const ALStream& stream) = default;
};
class ALWStream : public RefCount
{
public:
    virtual size_t vWrite(const void* buffer, size_t size) = 0;
    virtual bool vFlush() = 0;
    
    template<typename T>
    bool write(T v)
    {
        return this->vWrite(&v, sizeof(T));
    }
protected:
    ALWStream() = default;
    virtual ~ALWStream() = default;
};
class ALStreamFactory
{
public:
    static ALStream* readFromMem(const void* buffer);
    static ALWStream* writeForMem(void* buffer, int size);
    static ALStream* readFromFile(const char* file);
    static ALWStream* writeForFile(const char* file);
    
    typedef size_t(*READFUNC)(void* meta, void* buffer, size_t size);
    typedef size_t(*WRITEFUNC)(void* meta, const void* buffer, size_t size);
    typedef bool(*ENDFUNC)(void* meta);
    static ALStream* wrap(READFUNC r, ENDFUNC e, void* m);
    static ALWStream* wrapW(WRITEFUNC r, ENDFUNC e, void* m);

};
#endif
