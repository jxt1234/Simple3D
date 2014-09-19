#include "GL/GLBitmapWork.h"
static const char gVertex[] = 
"attribute vec2 aPos;\n"
"varying vec2 vTex;\n"
"void main(void)\n"
"{\n"
"gl_Position = vec4(aPos);\n"
"vTex = 0.5*(aPos+vec2(1.0));\n"
"}\n"
;

static const char gDefaultFrag[] = 
"varying vec2 vTex;\n"
"sampler2D bmp;\n"
"void main(void)\n"
"{\n"
"gl_FragColor = texture2D(bmp, vTex);\n"
"}\n"

GLBitmapWork::Shader::Shader(const char* fragSource, bool xlinear, bool ylinear, bool mipmiap, bool repeat)
{
    /*Construct Default Vertex Shader*/
    mProgram.load(gVertex, gDefaultFrag);
}

GLBitmapWork::Shader::~Shader()
{
}
int GLBitmapWork::Shader::setUp()
{
    mProgram.use();
    return mProgram.id();
}
