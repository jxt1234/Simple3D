#include "GL/GLTextureWork.h"
#include "GL/GLAutoFbo.h"
#include "GL/GLvboBuffer.h"
#include <sstream>


static const char gVertex[] = 
"attribute vec2 aPos;\n"
"varying vec2 vTex;\n"
"void main(void)\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, 1.0, 1.0);\n"
"vTex = 0.5*(aPos+1.0);\n"
"}\n"
;

static const char gDefaultFrag[] = 
"precision mediump float;\n"
"varying vec2 vTex;\n"
"uniform sampler2D buffer;\n"
"void main(void)\n"
"{\n"
"gl_FragColor = texture2D(buffer, vTex);\n"
"}\n"
;
GLTextureWork::GLTextureWork()
{
}

GLTextureWork::GLTextureWork(const char* vertex, const char* frag)
{
    if (NULL == vertex)
    {
        vertex = gVertex;
    }
    if (NULL == frag)
    {
        frag = gDefaultFrag;
    }
    mShader = new GLProgram;
    mShader->load(vertex, frag);
}
GLTextureWork::~GLTextureWork()
{
}

void GLTextureWork::DefaultVertex(std::ostream& vertex) const
{
    vertex << gVertex;
}
void GLTextureWork::setTexture(GPPtr<GLTexture> src, GPPtr<GLTexture> dst)
{
    mSrcT = src;
    mDstT = dst;
}
bool GLTextureWork::onPrepare()
{
    std::ostringstream vert, frag;
    if (this->onGenerateShader(vert, frag))
    {
        mShader = new GLProgram(vert.str(), frag.str());
    }
    GLASSERT(NULL!=mShader.get());
    return mShader->init();
}

void GLTextureWork::onDestroy()
{
    mSrcT = NULL;
    mDstT = NULL;
    if (NULL!=mShader.get())
    {
        mShader->destroy();
    }
}

void GLTextureWork::onProcess()
{
    assert(NULL!=mSrcT.get());
    assert(NULL!=mDstT.get());
    GLAutoFbo __f(*mDstT);
    mShader->use();
    int id = mShader->id();
    this->onUse(id, mSrcT->width(), mSrcT->height());
    mSrcT->use();
    /*TODO Use globle vbo buffer Optimize this*/
    const float points[] = {
        -1.0, -1.0,
        -1.0, 1.0,
        1.0, -1.0,
        1.0, 1.0
    };

    GLvboBuffer temp(points, 2, 4, GL_TRIANGLE_STRIP);
    temp.use(mShader->attr("aPos"));
    temp.draw();
}

void GLTextureWork::onFinish()
{
}
