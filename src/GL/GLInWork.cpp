#include "GL/GLInWork.h"
#include <sstream>

std::string GLInWork::gDefaultVertex =
"attribute vec2 aPos;\n"
"varying vec2 vTex;\n"
"void main(void)\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, 1.0, 1.0);\n"
"vTex = 0.5*(aPos+1.0);\n"
"}\n"
;

std::string GLInWork::gDefaultFrag =
"varying vec2 vTex;\n"
"uniform sampler2D inputImageTexture;\n"
"void main(void)\n"
"{\n"
"gl_FragColor = texture2D(buffer, vTex);\n"
"}\n"
;


GLInWork::GLInWork(const char* vertex, const char* frag, std::vector<GLBmp*> resouces)
{
    if (NULL == vertex)
    {
        vertex = gDefaultVertex.c_str();
    }
    if (NULL == frag)
    {
        frag = gDefaultFrag.c_str();
    }
    mProgram = new GLProgram(vertex, frag);
    mProgram->init();
    mResoucePos.clear();
    mResources.clear();
    for (int i=0; i<resouces.size(); ++i)
    {
        GLBmp* bmp = resouces[i];
        GPPtr<GLTexture> texture = new GLTexture();
        std::ostringstream os("inputImageTexture");
        os << i + 2;
        texture->upload(bmp->pixels(), bmp->getWidth(), bmp->getHeight());
        mResources.push_back(texture);
        mResoucePos.push_back(glGetUniformLocation(mProgram->id(), os.str().c_str()));
        OPENGL_CHECK_ERROR;//Call opengl directly, must check error
    }
}

GLInWork::~GLInWork()
{
}

void GLInWork::onSetupVertex()
{
    
}
void GLInWork::onSetupFragment()
{
    GLASSERT(mResoucePos.size() == mResources.size());
    for (int i=0; i<mResoucePos.size(); ++i)
    {
        GLTexture* t= mResources[i].get();
        int pos = mResoucePos[i];
        t->use(pos, i+1);
    }
}
void GLInWork::beforedraw()
{
    this->onSetupVertex();
    this->onSetupFragment();
}
void GLInWork::draw()
{
    /*TODO*/
}
void GLInWork::release()
{
    mResources.clear();
    mResoucePos.clear();
}
