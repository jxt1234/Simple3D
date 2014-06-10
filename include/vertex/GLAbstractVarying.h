#ifndef VERTEX_GLABSTRACTVARYING_H
#define VERTEX_GLABSTRACTVARYING_H

#include "interface/IVarying.h"
#include <vector>
#include <string.h>
class GLAbstractVarying:public IVarying
{
    public:
        GLAbstractVarying(int unit):mUnit(unit){}
        virtual ~GLAbstractVarying()
        {
            for (int i=0; i<mData.size(); ++i)
            {
                delete [] mData[i];
            }
        }
        virtual float* load(int pos) {return mData[pos];}
        virtual int unit(){return mUnit;}
        virtual int size() {return mData.size();}
        void print();
    protected:
        virtual float* alloc()
        {
            float* p = new float[mUnit];
            mData.push_back(p);
            return p;
        }
    private:
        std::vector<float*> mData;
        int mUnit;
};




#endif
