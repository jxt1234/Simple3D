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
GLBitmapWork::Shader::Shader(const char* fragSource)
{
    const char* frag = fragSource;
    /*Construct Default Vertex Shader*/
    if (NULL == frag) frag = gDefaultFrag;
    mProgram.load(gVertex, frag);
    /*TODO support for linear, mipmiap and repeat*/
}

GLBitmapWork::Shader::~Shader()
{
}
int GLBitmapWork::Shader::setUp()
{
    mProgram.init();
    return mProgram.id();
}

int GLBitmapWork::Shader::use()
{
    mProgram.use();
    return mProgram.id();
}


GLBitmapWork::GLBitmapWork(GLBmp* src, GLBmp* dst, Shader* shader)
{
    assert(NULL!=src);
    SAFE_REF(shader);
    mShader = shader;
    src->addRef();
    mSrc = src;
    if (NULL == dst)
    {
        dst = src;
    }
    mDst = dst;
    dst->addRef();
}
GLBitmapWork::~GLBitmapWork()
{
    SAFE_UNREF(mSrc);
    SAFE_UNREF(mDst);
}

bool GLBitmapWork::onPrepare()
{
    mSrcT = new GLTexture;
    mSrcT->upload(mSrc->pixels(), mSrc->width(), mSrc->height());
    mDstT = new GLTexture;
    mDstT->upload(NULL, mDst->width(), mDst->height());
    if (NULL == mShader.get())
    {
        mShader = new Shader;
    }
    int id = mShader->setUp();
    return id>0;
}

void GLBitmapWork::onProcess()
{
    GLAutoFbo __f(*mDstT);
    mShader->use();
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
    assert(mDst!=NULL);
    if (NULL!=mDstT.get())
    {
        GLAutoFbo __f(*mDstT);
        mDstT->download(mDst->pixels());
    }
}

void GLBitmapWork::onDestroy()
{
    mDstT = NULL;
    mSrcT = NULL;
    mShader = NULL;
}

