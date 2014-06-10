#ifndef FRAGMENT_GLABSTRACTRASTERIZATEDVARYING_H
#define FRAGMENT_GLABSTRACTRASTERIZATEDVARYING_H
#include "interface/head.h"
#include "interface/IRasterizatedVarying.h"
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <string>

class GLAbstractRasterizatedVarying:public IRasterizatedVarying
{
    public:
        GLAbstractRasterizatedVarying(int unit):mUnit(unit){}
        virtual ~GLAbstractRasterizatedVarying()
        {
            for (int i=0; i<mData.size(); ++i)
            {
                delete [] mData[i];
            }
        }
        virtual float* load(int pos) {return mData[pos];}
        virtual int unit(){return mUnit;}
        virtual int size() {return mData.size();}
        virtual void alloc(int size)
        {
            for (int i=0; i<size; ++i)
            {
                float* dat = new float[mUnit];
                mData.push_back(dat);
            }
        }
        std::string print();
    protected:
        std::vector<float*> mData;
        int mUnit;
};

class GLFixRasterizatedVarying:public IRasterizatedVarying
{
    public:
        GLFixRasterizatedVarying(int size, int unit):mUnit(unit), mData(NULL), mSize(0){mData = new float[unit*size];}
        virtual ~GLFixRasterizatedVarying(){delete [] mData;}
        virtual float* load(int pos) {return mData+pos*sizeof(float)*mUnit;}
        virtual int unit(){return mUnit;}
        virtual int size() {return mSize;}
        virtual void alloc(int size)
        {
            mSize+=size;
        }
    protected:
        float* mData;
        int mUnit;
        int mSize;
};

#endif
