#include "GL/GLFilterWork.h"
#include <sstream>
#include <iostream>
GLFilterWork::GLFilterWork(GLBmp* src, GLBmp* dst, const float* p, int n)
:GLMultiPassWork(src, dst)
{
    std::ostringstream os;
    float w = mSrc->width();
    float h = mSrc->height();
    _genShader(os, p, n, 1.0/w, 0);
    GPPtr<GLBitmapWork::Shader> s = new GLBitmapWork::Shader(os.str().c_str());
    addShader(s);
    os.str("");
    w = mDst->width();
    h = mDst->height();
    _genShader(os, p, n, 0, 1.0/h);
    s = new GLBitmapWork::Shader(os.str().c_str());
    addShader(s);
}

GLFilterWork::~GLFilterWork()
{
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
