#include "weightTable.h"
#include <assert.h>
#include <stdlib.h>
#define TRIANGLE 3
using namespace std;
weightTable::weightTable(int w, int h, float* p1, float* p2, float* p3)
{
    float x1 = p1[0];
    float x2 = p2[0];
    float x3 = p3[0];
    float y1 = p1[1];
    float y2 = p2[1];
    float y3 = p3[1];
    x1 = x1-x3;
    x2 = x2-x3;
    y1 = y1-y3;
    y2 = y2-y3;
    float det = x1*y2-x2*y1;
    w11 = -y2/det*2.0/w; w12 = x2/det*2.0/h; w13 = (x2*(y3-1)-y2*(x3-1))/det;
    w21 = y1/det*2.0/w; w22 = -x1/det*2.0/h; w23 = (-x1*(y3-1)+y1*(x3-1))/det;
    mData = NULL;
}
void weightTable::generate(IRasterizatedVarying* data, int sta)
{
    if (NULL!=mData) delete [] mData;
    mSize=data->size()-sta;
    assert(mSize>=0);
    mData = new float[mSize*TRIANGLE];
    float* r = mData;
    for (int i=sta; i<data->size(); ++i)
    {
        float* pos = data->load(i);
        getWeight(r, pos);
        r = r + TRIANGLE;
    }
}
void weightTable::rasterize(IRasterizatedVarying* output, float* x1, float* x2, float* x3)
{
    int unit = output->unit();
    int cur = output->size();
    output->alloc(mSize);
    for (int i=0; i<mSize; ++i)
    {
        float* w = mData+TRIANGLE*i;
        float* result = output->load(i+cur);
        for (int j=0; j<unit; ++j)
        {
            float y = w[0]*x1[j] + w[1]*x2[j] + w[2]*x3[j];
            result[j] = y;
        }
    }
}
/*First compute w from getWeight, and then compute z = w[0]*z1+w[1]*z2+w[2]*z3, and expand it to the equation below*/
/*z = k1*pos[0]+k2*pos[1]+k3*/
void weightTable::computeWeight(float& k1, float& k2, float& k3, float z1, float z2, float z3)
{
    k1 = w11*(z1-z3) + w21*(z2-z3);
    k2 = w12*(z1-z3) + w22*(z2-z3);
    k3 = z3 + w13*(z1-z3) + w23*(z2-z3);
}



weightTable::~weightTable()
{
    delete [] mData;
}
