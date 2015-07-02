#include "GL/GLDrawWork.h"
#include <sstream>


GLDrawWork::GLDrawWork(const std::string& vertex, const std::string& frag, std::vector<GLBmp*> resouces)
{
    mProgram = new GLProgram(vertex, frag);
    mProgram->init();
    mResoucePos.clear();
    mResources.clear();
    for (int i=0; i<resouces.size(); ++i)
    {
        GLBmp* bmp = resouces[i];
        GPPtr<GLTexture> texture = new GLTexture;
        std::ostringstream os("inputImageTexture");
        os << i + 2;
        texture->upload(bmp->pixels(), bmp->getWidth(), bmp->getHeight());
        mResources.push_back(texture);
        mResoucePos.push_back(glGetUniformLocation(mProgram->id(), os.str().c_str()));
        OPENGL_CHECK_ERROR;//Call opengl directly, must check error
    }
}

GLDrawWork::~GLDrawWork()
{
}

void GLDrawWork::onSetupVertex()
{
    
}
void GLDrawWork::onSetupFragment()
{
    GLASSERT(mResoucePos.size() == mResources.size());
    for (int i=0; i<mResoucePos.size(); ++i)
    {
        GLTexture* t= mResources[i].get();
        int pos = mResoucePos[i];
        t->use(pos, i+1);
    }
}
void GLDrawWork::onDraw(int srcid, int w, int h, GLvboBuffer* vs, GLvboBuffer* ts)
{
    GLASSERT(NULL!=vs);
    GLASSERT(NULL!=ts);
    mProgram->use();
    this->onSetupVertex();
    this->onSetupFragment();
    vs->use(mProgram->attr("position"));
    ts->use(mProgram->attr("textureCordinate"));
    vs->draw();
}
