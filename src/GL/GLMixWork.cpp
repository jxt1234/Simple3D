#include "GL/GLMixWork.h"
#include "GL/GLBitmapWorkFactory.h"
static const char* gFrag = 
"varying vec2 vTex;\n"
"uniform sampler2D buffer1;\n"
"uniform sampler2D buffer2;\n"
"void main(void)\n"
"{\n"
"gl_FragColor = texture2D(buffer1, vTex)*texture2D(buffer2, vTex);\n"
"}\n"
;
GLMixWork::GLMixWork()
{
}

GLMixWork::~GLMixWork()
{
}
bool GLMixWork::onGenerateShader(std::ostream& vertex, std::ostream& frag) const
{
    DefaultVertex(vertex);
    frag << gFrag;
}
void GLMixWork::onUse(GLTexture* dst, std::vector<GLTexture*> sources, GLProgram* shader)
{
    GLASSERT(sources.size()>=2);
    GLTexture* src1 = sources.at(0);
    GLTexture* src2 = sources.at(1);
    GLASSERT(NULL!=src1 && NULL!=src2);
    GLASSERT(NULL!=dst);
    int id = shader->id();
    int tid1 = glGetUniformLocation(id, "buffer1");
    int tid2 = glGetUniformLocation(id, "buffer2");
    src1->use(tid1, 0);
    src2->use(tid2, 1);
}
class GLMixWorkCreator:public GLBitmapWorkCreater
{
    public:
        virtual GLBitmapWork* vCreate(std::istream* input) const
        {
            GPPtr<GLTextureWork> work = new GLMixWork;
            return new GLBitmapWork(work);
        }
        virtual void vDetail(std::ostream& output) const
        {
        }
};


static GLBitmapWorkCreatorRegister<GLMixWorkCreator> __T("MixBitmap");
