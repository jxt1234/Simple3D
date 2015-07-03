#include "GL/GLDrawWork.h"
#include <sstream>

GLDrawWork::GLDrawWork(const std::string& vertex, const std::string& frag, const std::map<std::string, float>* uniforms , const std::vector<GLBmp*>* resources)
{
    mProgram = new GLProgram(vertex, frag);
    mProgram->init();
    mResoucePos.clear();
    mResources.clear();
    if (NULL!=resources)
    {
        const std::vector<GLBmp*>& resouces = *resources;
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
    if (NULL!=uniforms)
    {
        auto input_unifom = *uniforms;
        for (auto iter : input_unifom)
        {
            int pos = mProgram->uniform(iter.first.c_str());
            if (pos >= 0)
            {
                mUniforms.insert(std::make_pair(pos, iter.second));
            }
        }
    }
}

GLDrawWork::~GLDrawWork()
{
}
int GLDrawWork::vMap(double* parameters, int n)
{
    return 0;
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
void GLDrawWork::onDraw(GLTexture* src, GLvboBuffer* vs, GLvboBuffer* ts)
{
    GLASSERT(NULL!=vs);
    GLASSERT(NULL!=ts);
    GLASSERT(NULL!=src);
    mProgram->use();
    this->onSetupVertex();
    this->onSetupFragment();
    src->use(mProgram->uniform("inputImageTexture"),0);
    vs->use(mProgram->attr("position"));
    ts->use(mProgram->attr("inputTextureCoordinate"));
    for (auto iter:mUniforms)
    {
        GLProgram::setUniform(iter.second, iter.first);
    }
    vs->draw();
}
