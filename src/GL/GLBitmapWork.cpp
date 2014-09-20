#include "GL/GLBitmapWork.h"
#include "GL/GLAutoFbo.h"
#include "GL/GLvboBuffer.h"
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
;
GLBitmapWork::Shader::Shader(const char* fragSource, bool xlinear, bool ylinear, bool mipmiap, bool repeat)
{
    /*Construct Default Vertex Shader*/
    /*FIXME For debug*/
    mProgram.load(gVertex, gDefaultFrag);
    /*TODO support for linear, mipmiap and repeat*/
}

GLBitmapWork::Shader::~Shader()
{
}
int GLBitmapWork::Shader::setUp()
{
    mProgram.use();
    return mProgram.id();
}


GLBitmapWork::GLBitmapWork(GLBitmapWork::Shader* shader, GLBmp* src, GLBmp* dst)
{
    assert(NULL!=src);
    assert(NULL!=shader);
    src->addRef();
    mSrc = src;
    if (NULL == dst)
    {
        dst = src;
    }
    mDst = dst;
    dst->addRef();
    mSrcT = NULL;
    mDstT = NULL;

    shader->addRef();
    mShader = shader;
}
GLBitmapWork::GLBitmapWork(GLBitmapWork::Shader* shader, GLTexture* src, GLTexture* dst)
{
    assert(NULL!=src);
    assert(NULL!=dst);
    assert(NULL!=shader);
    src->addRef();
    dst->addRef();
    mSrcT = src;
    mDstT = dst;
    mSrc = NULL;
    mDst = NULL;
    shader->addRef();
    mShader = shader;
}
GLBitmapWork::~GLBitmapWork()
{
    SAFE_UNREF(mSrc);
    SAFE_UNREF(mDst);
    SAFE_UNREF(mSrcT);
    SAFE_UNREF(mDstT);
    SAFE_UNREF(mShader);
}

bool GLBitmapWork::onPrepare()
{
    if (NULL == mSrcT)
    {
        mSrcT = new GLTexture;
        mSrcT->upload(mSrc->pixels(), mSrc->width(), mSrc->height());
    }
    if (NULL == mDstT)
    {
        mDstT = new GLTexture;
        mDstT->upload(NULL, mDst->width(), mDst->height());
    }
    int id = mShader->setUp();
    assert(id > 0);//FIXME If id <= 0, return false
    return true;
}

void GLBitmapWork::onProcess()
{
    GLAutoFbo __f(*mDstT);
    mShader->setUp();
    const GLProgram& program = mShader->program();
    mSrcT->use();
    /*TODO Use globle vbo buffer Optimize this*/
    const float points[] = {
        -1.0, -1.0,
        -1.0, 1.0,
        1.0, -1.0,
        1.0, 1.0
    };

    GLvboBuffer temp(points, 2, 4, GL_TRIANGLE_STRIP);
    temp.use(program.attr("aPos"));
    temp.draw();
}

void GLBitmapWork::onFinish()
{
    /*Read result back from texture*/
    {
        GLAutoFbo __f(*mDstT);
        mDstT->download(mDst->pixels());
    }
    SAFE_UNREF(mDstT);
    SAFE_UNREF(mSrcT);
    SAFE_UNREF(mShader);
}
