//
//  ALStream.cpp
//  abs
//
//  Created by jiangxiaotang on 15/7/21.
//  Copyright (c) 2015年 jiangxiaotang. All rights reserved.
//

#include "utils/ALStream.h"
#include "ALFileStream.h"
#include "utils/debug.h"

ALStream*  ALStreamFactory::readFromFile(const char* file)
{
    return new ALFileStream(file);
}
ALWStream* ALStreamFactory::writeForFile(const char* file)
{
    return new ALWFileStream(file);
}

class ALStreamWrap:public ALStream
{
public:
    ALStreamWrap(ALStreamFactory::READFUNC r, ALStreamFactory::ENDFUNC e, void* meta)
    {
        GLASSERT(NULL!=mRead);
        GLASSERT(NULL!=mEnd);
        GLASSERT(NULL!=meta);
        mRead = r;
        mEnd = e;
        mMetaData = meta;
    }
    virtual ~ALStreamWrap()
    {
    }
    virtual size_t vRead(void* buffer, size_t size)
    {
        return mRead(mMetaData, buffer, size);
    }
    /*Return true if the stream has moved to end*/
    virtual bool vIsEnd() const
    {
        return mEnd(mMetaData);
    }
private:
    ALStreamFactory::READFUNC mRead;
    ALStreamFactory::ENDFUNC mEnd;
    void* mMetaData;
};
class ALWStreamWrap:public ALWStream
{
public:
    ALWStreamWrap(ALStreamFactory::WRITEFUNC r, ALStreamFactory::ENDFUNC e, void* meta)
    {
        GLASSERT(NULL!=mWrite);
        GLASSERT(NULL!=mEnd);
        GLASSERT(NULL!=meta);
        mWrite = r;
        mEnd = e;
        mMetaData = meta;
    }
    virtual ~ALWStreamWrap()
    {
    }
    virtual size_t vWrite(const void* buffer, size_t size)
    {
        return mWrite(mMetaData, buffer, size);
    }
    virtual bool vFlush()
    {
        return mEnd(mMetaData);
    }
private:
    ALStreamFactory::WRITEFUNC mWrite;
    ALStreamFactory::ENDFUNC mEnd;
    void* mMetaData;
};



ALStream* ALStreamFactory::wrap(READFUNC r, ENDFUNC e, void* m)
{
    return new ALStreamWrap(r, e, m);
}

ALWStream* ALStreamFactory::wrapW(WRITEFUNC r, ENDFUNC e, void* m)
{
    return new ALWStreamWrap(r, e, m);
}

