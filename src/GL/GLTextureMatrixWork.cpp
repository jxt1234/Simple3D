#include "GL/GLTextureMatrixWork.h"
static const char gVertex[] = 
"attribute vec2 aPos;\n"
"varying vec2 vTex;\n"
"uniform mat4 M;\n"
"void main(void)\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, 1.0, 1.0)*M;\n"
"vTex = 0.5*(aPos+1.0);\n"
"}\n"
;
GLTextureMatrixWork::GLTextureMatrixWork(const GLMatrix4& matrix):GLTextureWork(gVertex, NULL)
{
    mMatrix = matrix;
}
GLTextureMatrixWork::~GLTextureMatrixWork()
{
}

void GLTextureMatrixWork::onUse(GLTexture* dst, std::vector<GLTexture*> sources, GLProgram* shader)
{
    GLProgram::setMatrix(mMatrix, shader->uniform("M"));
}
