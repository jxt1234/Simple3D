#include "GL/GLDrawWork.h"
#include <sstream>
static const char* gTextureVaryName = "inputImage";
GLDrawWork::GLDrawWork(const std::string& vertex, const std::string& frag, const std::map<std::string, float>* uniforms , const std::vector<GLBmp*>* resources, int inputnumber)
{
    mProgram = new GLProgram(vertex, frag);
    mProgram->init();
    mResoucePos.clear();
    mResources.clear();
    for (int i=0; i<inputnumber; ++i)
    {
        std::ostringstream os;
        os << gTextureVaryName;
        if (i!=0)
        {
            os << i;
        }
        mInputPos.push_back(mProgram->uniform(os.str().c_str()));
        GLASSERT(mInputPos[mInputPos.size()-1]>=0);
    }
    if (NULL!=resources)
    {
        const std::vector<GLBmp*>& resouces = *resources;
        for (int i=0; i<resouces.size(); ++i)
        {
            GLBmp* bmp = resouces[i];
            GPPtr<GLTexture> texture = new GLTexture;
            std::ostringstream os;
            os << gTextureVaryName;
            os << i + inputnumber + 1;
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
                mUniformOrder.insert(std::make_pair(iter.first, pos));
            }
        }
    }
    mTextureCorderPos = mProgram->attr("inputTextureCoordinate");
    mVertexPos = mProgram->attr("position");
    GLASSERT(mTextureCorderPos >= 0);
    GLASSERT(mVertexPos >= 0);
}

GLDrawWork::~GLDrawWork()
{
}

void GLDrawWork::setUniform(const std::string& name, float value)
{
    auto iter = mUniformOrder.find(name);
    if (iter != mUniformOrder.end())
    {
        int pos = iter->second;
        mUniforms[pos] = value;
    }
}
size_t GLDrawWork::vMap(double* parameters, size_t n)
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
void GLDrawWork::onDraw(GLTexture** src, int number, GLvboBuffer* vs, GLvboBuffer* ts)
{
    GLASSERT(NULL!=vs);
    GLASSERT(NULL!=ts);
    GLASSERT(NULL!=src);
    GLASSERT(number == mInputPos.size());
    mProgram->use();
    this->onSetupVertex();
    this->onSetupFragment();
    for (int i=0; i<number; ++i)
    {
        GLASSERT(NULL!=src[i]);
        src[i]->use(mInputPos[i], i);
    }
    vs->use(mVertexPos);
    ts->use(mTextureCorderPos);
    for (auto iter:mUniforms)
    {
        GLProgram::setUniform(iter.second, iter.first);
    }
    vs->draw();
}
