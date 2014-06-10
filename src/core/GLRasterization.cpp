#include "core/GLRasterization.h"
#include <assert.h>
#include "utils/debug.h"
#include "weightTable.h"
#include "fragment/GLAbstractRasterizatedVarying.h"

using namespace std;

class linearFunc
{
    public:
        linearFunc(float k1, float k2, float k3)
        {
            c1 = k1;
            c2 = k2;
            c3 = k3;
        }
        float compute(int x, int y)
        {
            return c1*x+c2*y+c3;
        }
        ~linearFunc(){}
        float c1;
        float c2;
        float c3;
};


#define SWAP(x, y) temp = x;x=y;y=temp;
static void _DrawAngle_flat(IRasterizatedVarying* output, int x1, int y1, int x21, int x22, int y2, int width, int height, GLDepthBuffer* buffer, linearFunc* func)
{
    int temp;
    if (x21 > x22){SWAP(x21, x22);}
    /*Compute the two lines' slope*/
    /*y1, y2 will be changed after*/
    float k1 = (float)(x1 - x21) / (float)(y1 - y2);
    float k2 = (float)(x1 - x22) / (float)(y1 - y2);
    int basY = y2;
    if (y1 > y2){SWAP(y1, y2);}
    if (y1 < 0) y1 = 0;
    if (y2 >= height) y2 = height -1;
    if (NULL==buffer)
    {
        for (int i=y1; i<=y2; ++i)
        {
#define LEFT_RIGHT\
            int xleft = k1*(i-basY) + x21;\
            if (xleft >= width) continue;\
            if (xleft < 0) xleft = 0;\
            int xright = k2*(i-basY) + x22;\
            if (xright<0) continue;\
            if (xright >= width) xright = width - 1;\
            if (xleft > xright) continue;
            LEFT_RIGHT;
            int cur = output->size();
            output->alloc(xright-xleft+1);
            for (int j = xleft; j<=xright; ++j)
            {
                float* mid = output->load(cur++);
                mid[0] = j;
                mid[1] = i;
            }
        }
    }
    else
    {
        for (int i=y1; i<=y2; ++i)
        {
            LEFT_RIGHT;
            int cur = output->size();
            for (int j = xleft; j<=xright; ++j)
            {
                float z = func->compute(j, i);
                if (buffer->valid(z, j, i))
                {
                    output->alloc(1);
                    float* mid = output->load(cur++);
                    mid[0] = j;
                    mid[1] = i;
                }
                else
                {
                }
            }
        }
    }
}

static void _DrawAngle(IRasterizatedVarying* output, int x1, int y1, int x2, int y2, int x3, int y3, int width, int height, GLDepthBuffer* buffer, linearFunc* func)
{
    int temp;
    /*Assume that y1>y2>y3*/
    if (y1 < y2)
    {
        SWAP(x1, x2);
        SWAP(y1, y2);
    }
    if (y2 < y3)
    {
        SWAP(y2, y3);
        SWAP(x2, x3);
    }
    if (y1 < y2)
    {
        SWAP(x1, x2);
        SWAP(y1, y2);
    }
    /*Compute the mid xm, when ym = y2*/
    float k = (float)(y1-y3)/(float)(x1-x3);
    int xm = (y2-y3)/k + x3;
    _DrawAngle_flat(output, x1, y1, x2, xm, y2, width, height, buffer, func);
    _DrawAngle_flat(output, x3, y3, x2, xm, y2, width, height, buffer, func);
}


void GLRasterization(std::vector<IVarying*> inputs, std::vector<IRasterizatedVarying*> outputs, int width, int height, GLDepthBuffer* buffer)
{
    assert(outputs.size() == inputs.size());
    assert(!outputs.empty());
    assert(inputs[0]->size()%3 == 0);
    assert(width > 0 && height > 0);
    if (NULL!=buffer) assert(inputs[0]->unit()>=3);
    //The first input is gl_position with unit 3 or 4 and the first output is gl_fragposition with unit 2, they needn't be equal
    for (int i=1;i<outputs.size(); ++i)
    {
        assert(inputs[i]->size() == inputs[0]->size());
        assert(outputs[i]->unit() <= inputs[i]->unit());
    }
    IVarying* pos = inputs[0];
    int weightpos = 0;
    for (int i=0; i<pos->size();i+=3)
    {
    //Generate weightTable, the first element of inputs is used to generated it
        float* p1 = pos->load(i);
        float* p2 = pos->load(i+1);
        float* p3 = pos->load(i+2);
#define POS(x, w) (w-(x+1)/2.0*w)
        int x1 = POS(p1[0], width);
        int y1 = POS(p1[1], height);
        int x2 = POS(p2[0], width);
        int y2 = POS(p2[1], height);
        int x3 = POS(p3[0], width);
        int y3 = POS(p3[1], height);
#undef POS
        weightTable weight(width, height, p1, p2, p3);
        if (NULL!=buffer)
        {
            float k1, k2, k3;
            weight.computeWeight(k1, k2, k3, p1[2], p2[2], p3[2]);
            linearFunc func(k1, k2, k3);
        _DrawAngle(outputs[0], x1, y1, x2, y2, x3, y3, width, height, buffer, &func);
        }
        else
        {
            _DrawAngle(outputs[0], x1, y1, x2, y2, x3, y3, width, height, NULL, NULL);
        }
        if (outputs.size() > 1)
        {
            weight.generate(outputs[0], weightpos);
            //Rasterization varying value base on the decision
            for (int j=1; j<outputs.size(); ++j)
            {
                IVarying* inp = inputs[j];
                float* sp1 = inp->load(i);
                float* sp2 = inp->load(i+1);
                float* sp3 = inp->load(i+2);
                weight.rasterize(outputs[j], sp1, sp2, sp3);
            }
            weightpos = outputs[0]->size();
        }
    }
}



void GLCSVertexGenerate(IVarying* pos, IVarying* normal, IVarying* tex, GLCurveSurface* cs, GLRectArea* area, int type)
{
    float u1 = area->x1;
    float u2 = area->x2;
    float v1 = area->y1;
    float v2 = area->y2;
    float u_interval = area->ux;
    float v_interval = area->uy;
    //TODO replace assert by swap u1, u2 if u1>u2
    assert(u1 < u2);
    assert(v1 < v2);
    int uNumber = (u2-u1)/u_interval;
    int vNumber = (v2-v1)/v_interval;
    if (u1+uNumber*u_interval < u2) uNumber++;
    if (v1+vNumber*v_interval < v2) vNumber++;
    //TODO uNumber<=0 may occur and should be allowed, now is for debug
    assert(uNumber>0);
    assert(vNumber>0);
    float u_1, u_2, v_1, v_2;
    float *p;
    float *v;
    float *t;
    for (int i=0; i<uNumber; ++i)
    {
        for (int j=0; j<vNumber; ++j)
        {
            u_1 = u_interval*i + u1;
            u_2 = u_interval*(i+1) + u1;
            v_1 = v_interval*j + v1;
            v_2 = v_interval*(j+1) + v1;
#define ALLOC(U, V) \
            p = pos->alloc(); \
            v = normal->alloc(); \
            t = tex->alloc(); \
            cs->pos(p, U, V); \
            cs->normal(v, U, V); \
            t[0] = U; t[1] = V;

            //Alloc the first triangle
            ALLOC(u_1, v_1);
            ALLOC(u_2, v_1);
            ALLOC(u_1, v_2);
            //Alloc the second triangle
            ALLOC(u_2, v_1);
            ALLOC(u_1, v_2);
            ALLOC(u_2, v_2);
#undef ALLOC
        }
    }
}

