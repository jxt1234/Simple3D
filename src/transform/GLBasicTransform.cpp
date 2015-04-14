#include "transform/GLBasicTransform.h"
#include <math.h>
#define PI 3.141592654

#include "core/GLRasterization.h"
#include "vertex/GL_position.h"
#include "fragment/GL_FragPosition.h"
#include "vertex/GL_texcord.h"
#include "fragment/GL_FragTexcord.h"
#include "utils/debug.h"
#include "interface/IVertexFunction.h"

using namespace std;

static vector<float> _rotate(float x, float y, float rad, float sw=1.0, float sh=1.0, float dw=1.0, float dh=1.0)
{
    x = x*sw;
    y = y*sh;
    vector<float> r;
    float x_ = x*cos(rad) + y*sin(rad);
    float y_ = y*cos(rad) - x*sin(rad);
    x_ /=dw;
    y_ /=dh;
    r.push_back(x_);
    r.push_back(y_);
    r.push_back(1);
    return r;
}

void GLRotate(IBitmap& src, IBitmap& dst, float degree, bool scale)
{
    //Change to radium
    assert(4 == src.getBpp());
    assert(4 == dst.getBpp());
    degree = degree * PI / 180.0;
    GL_texcord tex;
    tex.addPoint(0.0, 0.0);
    tex.addPoint(0.0, 1.0);
    tex.addPoint(1.0, 0.0);
    tex.addPoint(0.0, 1.0);
    tex.addPoint(1.0, 0.0);
    tex.addPoint(1.0, 1.0);
    GL_position pos;
    vector<float> v1, v2, v3, v4, v5, v6;
    if (scale)
    {
        v1 = (_rotate(-1, 1, degree));
        v2 = (_rotate(-1, -1, degree));
        v3 = (_rotate(1, 1, degree));
        v4 = (_rotate(-1, -1, degree));
        v5 = (_rotate(1, 1, degree));
        v6 = (_rotate(1, -1, degree));
    }
    else
    {
        v1 = (_rotate(-1,  1, degree,src.getWidth(), src.getHeight(), dst.getWidth(), dst.getHeight()));
        v2 = (_rotate(-1, -1, degree,src.getWidth(), src.getHeight(), dst.getWidth(), dst.getHeight()));
        v3 = (_rotate( 1,  1, degree,src.getWidth(), src.getHeight(), dst.getWidth(), dst.getHeight()));
        v4 = (_rotate(-1, -1, degree,src.getWidth(), src.getHeight(), dst.getWidth(), dst.getHeight()));
        v5 = (_rotate( 1,  1, degree,src.getWidth(), src.getHeight(), dst.getWidth(), dst.getHeight()));
        v6 = (_rotate( 1, -1, degree,src.getWidth(), src.getHeight(), dst.getWidth(), dst.getHeight()));
    }
    pos.addVector(v1);
    pos.addVector(v2);
    pos.addVector(v3);
    pos.addVector(v4);
    pos.addVector(v5);
    pos.addVector(v6);
    GL_FragPosition f;
    GL_FragTexcord ftex(src.getWidth(), src.getHeight());
    vector<IVarying*> inputs;
    inputs.push_back(&pos);
    inputs.push_back(&tex);
    vector<IRasterizatedVarying*> outputs;
    outputs.push_back(&f);
    outputs.push_back(&ftex);
    GLRasterization(inputs, outputs, dst.getWidth(), dst.getHeight());

    for (int i=0; i<f.size(); ++i)
    {
        float* pos = f.load(i);
        vector<int> texc = ftex.loadInt(i);
        int x = pos[0];
        int y = pos[1];
        int u = texc[0];
        int v = texc[1];
        uint32_t* _src = (uint32_t*)src.vGetAddr(u,v);
        uint32_t* _dst = (uint32_t*)dst.vGetAddr(x,y);
        *_dst = *_src;
    }
}

