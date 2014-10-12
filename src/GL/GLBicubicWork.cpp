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

float BiCubicPoly(float x, float a)
{
    if (x<0) x = -x;
    float res = 0.0;
    if(x <= 1.0)
    {
        res = (a+2)*x*x*x - (a+3)*x*x + 1;
    }
    else if(x < 2.0)
    {
        res = a*x*x*x - 5*a*x*x + 8*a*x - 4*a;
    }
    return res;
}
void GLBicubicWork::onUse(int proId, int srcW, int srcH)
{
    float uUnit = 1.0/(float)srcW;
    float vUnit = 1.0/(float)srcH; 
    int uid = glGetUniformLocation(proId, "uUnit");
    OPENGL_CHECK_ERROR;
    glUniform1f(uid, uUnit);
    OPENGL_CHECK_ERROR;
    int vid = glGetUniformLocation(proId, "vUnit");
    OPENGL_CHECK_ERROR;
    glUniform1f(vid, vUnit);
    OPENGL_CHECK_ERROR;
}
bool GLBicubicWork::onGenerateShader(std::ostream& vertex, std::ostream& frag) const
{
    DefaultVertex(vertex);
    _genShader(frag);
}

void GLBicubicWork::_genShader(std::ostream& os) const
{
    os <<"precision mediump float;\n";
    os <<"varying vec2 vTex;\n";
    os <<"uniform sampler2D buffer;\n";
    os <<"uniform float uUnit;\n";
    os <<"uniform float vUnit;\n";
    os <<"void main()\n{\n";
    os <<"gl_FragColor = vec4(0.0,0.0,0.0,0.0)\n";
    const int n = 4;
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            float uOff = (i-n/2)+0.5;
            float vOff = (j-n/2)+0.5;
            float p = BiCubicPoly(uOff, mA)*BiCubicPoly(vOff, mA);
            os <<"+ float("<<p<<")*texture2D(buffer, vTex + vec2(float("<<uOff<<")*uUnit, float("<<vOff<<")*vUnit))\n";
        }
    }
    os <<";\n"<<"}\n";
}


class GLBicubicWorkCreater:public GLBitmapWorkCreater
{
    public:
        virtual GLBitmapWork* vCreate(std::istream* input) const
        {
            float a = -0.5;
            if (NULL!=input)
            {
                (*input)>>a;
            }
            GPPtr<GLTextureWork> w = new GLBicubicWork(a);
            return new GLBitmapWork(w);
        }
        virtual void vDetail(std::ostream& os) const
        {
            os << "Input: a, default 0.5"<<std::endl;
        }
};

static GLBitmapWorkCreatorRegister<GLBicubicWorkCreater> __T("Bicubic");
