#include "GL/GLFilterWork.h"
#include "GL/GLBitmapWorkFactory.h"
#include <sstream>
#include <iostream>
#include <string.h>
GLFilterWork::GLFilterWork(GLBmp* src, GLBmp* dst, const float* p, int n):GLMultiPassWork(src, dst)
{
    assert(n>1);
    mP = new float[n];
    mN = n;
    memcpy(mP, p, n*sizeof(float));
    if (NULL!=mSrc.get() && NULL!=mDst.get())
    {
        _buildShaders();
    }
}

GLFilterWork::~GLFilterWork()
{
    delete [] mP;
}

void GLFilterWork::_buildShaders()
{
    clearShaders();
    std::ostringstream os;
    float w = mSrc->width();
    float h = mSrc->height();
    _genShader(os, mP, mN, 1.0/w, 0);
    GPPtr<GLBitmapWork::Shader> s = new GLBitmapWork::Shader(os.str().c_str());
    addShader(s);
    os.str("");
    w = mDst->width();
    h = mDst->height();
    _genShader(os, mP, mN, 0, 1.0/h);
    s = new GLBitmapWork::Shader(os.str().c_str());
    addShader(s);
}

void GLFilterWork::onSet()
{
    _buildShaders();
}

void GLFilterWork::_genShader(std::ostream& os, const float* p, int n, float x, float y)
{
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

class GLFilterWork_Creater:public GLBitmapWorkCreater
{
    public:
        virtual GLBitmapWork* vCreate(std::istream* input) const
        {
            GLBitmapWork* w = NULL;
            if (NULL == input)
            {
                const float p[] = {0.2, 0.6,0.2};
                w = new GLFilterWork(NULL, NULL, p, sizeof(p)/sizeof(float));
                return w;
            }
            std::istream& is = *input;
            int n;
            is >> n;
            assert(n>1);
            float* p = new float[n];
            for (int i=0; i<n; ++i)
            {
                is >> p[i];
            }
            delete [] p;
            return w;
        }
        virtual void vDetail(std::ostream& os) const
        {
            os << "Input: n x0 x1 x2 ... ... x(n-1)"<<std::endl;
            os << "If NULL == input, the default will be 0.2 0.6 0.2"<<std::endl;
        }
};

static GLBitmapWorkCreatorRegister<GLFilterWork_Creater> __T("Filter");
