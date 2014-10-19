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
static const char* BiCubicPoly1 = 
"float BiCubicPoly1(float x, float a)\n"
"{\n"
"    x = abs(x);\n"
"    float res = (a+float(2))*x*x*x - (a+float(3))*x*x + float(1);\n"
"    return res;\n"
"}\n"
;
static const char* BiCubicPoly2 = 
"float BiCubicPoly2(float x, float a)\n"
"{\n"
"    x = abs(x);\n"
"    float res = a*x*x*x - float(5)*a*x*x + float(8)*a*x - float(4)*a;\n"
"    return res;\n"
"}\n"
;
void GLBicubicWork::onUse(GLTexture* dst, std::vector<GLTexture*> sources, GLProgram* shader)
{
    int proId = shader->id();
    int srcW = (sources.at(0))->width();
    int srcH = (sources.at(0))->height();
    float uUnit = (float)srcW;
    float vUnit = (float)srcH; 
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
    //_genShader(std::cout);
    _genShader(frag);
    return true;
}

void GLBicubicWork::_genShader(std::ostream& os) const
{
    os <<"precision mediump float;\n";
    os <<"varying vec2 vTex;\n";
    os <<"uniform sampler2D buffer;\n";
    os <<"uniform float uUnit;\n";
    os <<"uniform float vUnit;\n";
    os <<"\n";
    os <<BiCubicPoly1<<BiCubicPoly2;
    os <<"void main()\n{\n";
    os <<"vec2 basic; \n";
    os <<"vec2 det; \n";
    os <<"basic = vTex*vec2(uUnit, vUnit) - vec2(0.5,0.5); \n";
    os <<"det = fract(basic); \n";
    os <<"gl_FragColor = vec4(0.0,0.0,0.0,0.0)\n";
    const int n = 4;
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            int uOff = (i-n/2)+1;
            int vOff = (j-n/2)+1;
            os << "+";
            if (i==1||i==2) os << "BiCubicPoly1";
            else os << "BiCubicPoly2";
            os <<"(det.x-float("<<uOff<<"), float("<<mA<<"))*";
            if (j==1||j==2) os << "BiCubicPoly1";
            else os << "BiCubicPoly2";
            os <<"(det.y-float("<<vOff<<"), float("<<mA<<"))*";
            os << "texture2D(buffer, vTex + ( - det + vec2(float("<<uOff<<"), float("<<vOff<<")))/vec2(uUnit, vUnit))\n";
            //os << "texture2D(buffer, (basic)/vec2(uUnit, vUnit))\n";
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
