#include "GL/GLBitmapWork.h"
#include "GL/GLAutoFbo.h"
#include "GL/GLvboBuffer.h"
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
"varying vec2 vTex;\n"
"uniform sampler2D buffer;\n"
"void main(void)\n"
"{\n"
"gl_FragColor = texture2D(buffer, vTex);\n"
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


GLBitmapWork::GLBitmapWork(GLBmp* src, GLBmp* dst, Shader* shader)
{
    assert(NULL!=src);
    if (NULL == shader)
    {
        mShader = new Shader;
    }
    else
    {
        shader->addRef();
        mShader = shader;
    }
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
}
GLBitmapWork::GLBitmapWork(GLTexture* src, GLTexture* dst, Shader* shader)
{
    assert(NULL!=src);
    assert(NULL!=dst);
    src->addRef();
    dst->addRef();
    mSrcT = src;
    mDstT = dst;
    mSrc = NULL;
    mDst = NULL;
    if (NULL == shader)
    {
        mShader = new Shader;
    }
    else
    {
        shader->addRef();
        mShader = shader;
    }
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
