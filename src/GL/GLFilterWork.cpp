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
    _genShader(frag, mP, mN);
    return true;
}
void GLFilterWork::onUse(GLTexture* dst, std::vector<GLTexture*> sources, GLProgram* shader)
{
    float offset[2] = {0.0f,0.0f};
    if (mPass == 0)
    {
        int w = (sources.at(0))->width();
        offset[0] = 1.0f/(float)w;
    }
    else
    {
        int h = (sources.at(0))->height();
        offset[1] = 1.0f/(float)h;
    }
    int id = shader->id();
    int uid = glGetUniformLocation(id, "offset");
    OPENGL_CHECK_ERROR;
    glUniform2fv(uid, 1, offset);
    OPENGL_CHECK_ERROR;
}

void GLFilterWork::_genShader(std::ostream& os, const float* p, int n)
{
    os <<"varying vec2 vTex;\n";
    os <<"uniform vec2 offset;\n";
    os <<"uniform sampler2D buffer;\n";
    os <<"void main()\n{\n";
    os <<"gl_FragColor = vec4(0.0,0.0,0.0,0.0)\n";
    for (int i=0; i<n; ++i)
    {
        int pos = i-n/2;
        os <<"+ "<<p[i]<<"*texture2D(buffer, vTex + float("<<pos<<")*offset)\n";
    }
    os <<";\n";
    os <<"}\n";
}
bool GLFilterWork::vCurrent(GLProgram** program) const
{
    if (mPass>=gTotolPass)
    {
        return false;
    }
    return true;
}
void GLFilterWork::vNext()
{
    mPass++;
}

void GLFilterWork::vRewind()
{
    mPass = 0;
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
