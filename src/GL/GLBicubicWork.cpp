#include "GL/GLBitmapWorkFactory.h"
#include "GL/GLBicubicWork.h"
#include <sstream>
#include <math.h>

GLBicubicWork::GLBicubicWork(float a):mA(a)
{
}
GLBicubicWork::~GLBicubicWork()
{
}

void GLBicubicWork::onSet()
{
    int w = mSrc->width();
    int h = mSrc->height();
    std::ostringstream os;
    _genShader(os, w, h);
    mShader = new Shader(os.str().c_str());
}

float BiCubicPoly(float x)
{
    float abs_x = abs(x);
    float a = -0.5;
    if( abs_x <= 1.0 )
    {
        return (a+2)*pow(abs_x,3) - (a+3)*pow(abs_x,2) + 1;
    }
    else if( abs_x < 2.0 )
    {
        return a*pow(abs_x,3) - 5*a*pow(abs_x,2) + 8*a*abs_x - 4*a;
    }
    else
        return 0.0;
}

void GLBicubicWork::_genShader(std::ostream& os, int w, int h)
{
    os <<"precision mediump float;\n";
    os <<"varying vec2 vTex;\n";
    os <<"uniform sampler2D buffer;\n";
    os <<"void main()\n{\n";
    os <<"gl_FragColor = vec4(0.0,0.0,0.0,0.0)\n";
    const int n = 4;
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            float uOff = (i+1-n/2)/(float)w;
            float vOff = (j+1-n/2)/(float)h;
            float p = BiCubicPoly(uOff*w)*BiCubicPoly(vOff*h);
            os <<"+ "<<p<<"*texture2D(buffer, vTex + vec2("<<uOff<<", "<<vOff<<"))\n";
        }
    }
    os <<";\n"<<"}\n";
}


class GLBicubicWorkCreater:public GLBitmapWorkCreater
{
    public:
        virtual GLBitmapWork* vCreate(std::istream* input) const
        {
            float a = 0.5;
            if (NULL!=input)
            {
                (*input)>>a;
            }
            GLBitmapWork* w = new GLBicubicWork(a);
            return w;
        }
        virtual void vDetail(std::ostream& os) const
        {
            os << "Input: a, default 0.5"<<std::endl;
        }
};

static GLBitmapWorkCreatorRegister<GLBicubicWorkCreater> __T("Bicubic");
