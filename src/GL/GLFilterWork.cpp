#include "GL/GLFilterWork.h"
#include "GL/GLBitmapWorkFactory.h"
#include <sstream>
#include <iostream>
#include <string.h>
static const int gTotolPass = 2;
GLFilterWork::GLFilterWork(const float* p, int n)
{
    assert(n>1);
    mP = new float[n];
    mN = n;
    memcpy(mP, p, n*sizeof(float));
    mPass = 0;
}

GLFilterWork::~GLFilterWork()
{
    delete [] mP;
}

bool GLFilterWork::onGenerateShader(std::ostream& vertex, std::ostream& frag) const
{
    GLASSERT(mPass<=1);
    DefaultVertex(vertex);
    float x=0.0,y=0.0;
    if (0==mPass)
    {
        x = 1.0/(float)(src_()->width());
    }
    else if (1==mPass)
    {
        y = 1.0/(float)(src_()->height());
    }
    _genShader(frag, mP, mN, x, y);
    return true;
}

void GLFilterWork::_genShader(std::ostream& os, const float* p, int n, float x, float y)
{
    os <<"precision mediump float;\n";
    os <<"varying vec2 vTex;\n";
    os <<"uniform sampler2D buffer;\n";
    os <<"void main()\n{\n";
    os <<"gl_FragColor = vec4(0.0,0.0,0.0,0.0)\n";
    for (int i=0; i<n; ++i)
    {
        os <<"+ "<<p[i]<<"*texture2D(buffer, vTex + vec2("<<(i-n/2)*x<<", "<<(i-n/2)*y<<"))\n";
    }
    os <<";\n";
    os <<"}\n";
}
bool GLFilterWork::vFinish() const
{
    return mPass>=gTotolPass;
}
void GLFilterWork::vNext()
{
    mPass++;
}

class GLFilterWork_Creater:public GLBitmapWorkCreater
{
    public:
        virtual GLBitmapWork* vCreate(std::istream* input) const
        {
            GPPtr<GLTextureWork> w;
            if (NULL == input)
            {
                const float p[] = {0.2, 0.6,0.2};
                w = new GLFilterWork(p, sizeof(p)/sizeof(float));
                return new GLBitmapWork(w);
            }
            std::istream& is = *input;
            int n;
            is >> n;
            GLASSERT(n>1);
            float* p = new float[n];
            for (int i=0; i<n; ++i)
            {
                is >> p[i];
            }
            w = new GLFilterWork(p, sizeof(p)/sizeof(float));
            delete [] p;
            return new GLBitmapWork(w);
        }
        virtual void vDetail(std::ostream& os) const
        {
            os << "Input: n x0 x1 x2 ... ... x(n-1)"<<std::endl;
            os << "If NULL == input, the default will be 0.2 0.6 0.2"<<std::endl;
        }
};

static GLBitmapWorkCreatorRegister<GLFilterWork_Creater> __T("Filter");
