#include "GL/GLBitmapWork.h"
#include "GL/GLBitmapWorkFactory.h"
#include "utils/GPRandom.h"
#include <math.h>
#include <sstream>
#include <iostream>
static const char head[] = 
"precision mediump float;\n"
"varying vec2 vTex;\n"
"void main(void)\n"
"{\n"
;
static const char tail[] = 
"}\n"
;

static void _genShaderFrac(std::ostream& os, int n, int iternumber, float kR, float kG, float kB, float pR, float pG, float pB, float w, float h)
{
    os << head;
    os << "vec2 p = (2.0*vTex-1.0)*vec2("<<w<<", "<<h<<"); vec2 q;\n";
    os << "const vec4 cweight = vec4("<<pR<<","<<pG<<", "<<pB<<", 1.0);\n";
    os << "const vec3 weight1 = vec3("<<kR<<","<<kG<<", "<<-kB<<");\n";
    os << "const vec3 weight2 = vec3("<<kR<<", "<<-kG<<", "<<kB<<");\n";
    os << "const vec3 weight3 = vec3("<<-kR<<","<<kG<<", "<<kB<<");\n";
    os << "float seta, r, sl;\n";
    os << "vec3 dl;\n";
    os << "vec4 color;\n";
    float n_1 = n-1;
    for (int i=0; i<iternumber; ++i)
    {
#define ITER \
        os << "q = p;\n";\
        os <<"seta = atan(q.y, q.x);\n";\
        os << "r = length(q);\n";\
        os << "r = r*"<<(float)n-1/(float)n<<";\n";\
        os << "sl = float(1.0)/pow(r, "<<n-1<<");\n";\
        os << "p.x = r*cos(seta) + sl*cos(seta*float("<<(1-n)<<"));\n";\
        os << "p.y = r*sin(seta) + sl*sin(seta*float("<<(1-n)<<"));\n";

        ITER;
    }
    os <<"dl.x = 0.6*log(abs(p.x-q.x)*abs(p.y-q.y));\n";
    os <<"dl.y = 1.2*log(distance(p, q));\n";
    ITER;
    os <<"dl.z = 2.0*log(abs(p.x-q.x)*abs(p.y-q.y));\n";
#undef ITER
    os << "color.r = dot(dl, weight1);\n";
    os << "color.g = dot(dl, weight2);\n";
    os << "color.b = dot(dl, weight3);\n";
    os << "color = color*cweight;\n";
    os << "color = fract(color);\n";
    os << "color.a = 1.0;\n";
    os << "gl_FragColor = color;\n";
    os <<tail;
}

class GLFractionCreator:public GLBitmapWorkCreater
{
    public:
        virtual GLBitmapWork* vCreate(std::istream* input) const;
        virtual void vDetail(std::ostream& output) const;
};

GLBitmapWork* GLFractionCreator::vCreate(std::istream* input) const
{
    /*TODO Support input*/
    /*Default*/
    int n;
    {
        static const int CountList[]={3,3,3,3,4,4,5,5,6,7,8};
        float pos = GPRandom::rate();
        int _p = pos*sizeof(CountList)/sizeof(int);
        n = CountList[_p];
    }
    float kR, kG, kB, pR, pG, pB;
    {
        kR = 2.0*GPRandom::rate()-1.0;
        kG = 2.0*GPRandom::rate()-1.0;
        kB = 2.0*GPRandom::rate()-1.0;

        pR = GPRandom::rate();
        pG = GPRandom::rate();
        pB = GPRandom::rate();
        double r=1.0/(1<<(n-3));
        r=pow(r,0.095);
    }
    int iternumber = GPRandom::mid(1, 6);
    std::ostringstream os;
    _genShaderFrac(os, n, iternumber, kR, kG, kB, pR, pG, pB, 0.1,0.1);
    GPPtr<GLTextureWork> work = new GLTextureWork(NULL, os.str().c_str());
    return new GLBitmapWork(work);
}


void GLFractionCreator::vDetail(std::ostream& output) const
{
}


static GLBitmapWorkCreatorRegister<GLFractionCreator> __T("Fraction");
