#include "GL/GLBitmapWork.h"
#include "GL/GLAutoFbo.h"
#include "GL/GLvboBuffer.h"
#include "GL/GLBitmapWorkFactory.h"
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
    mProgram.destroy();
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
    if (NULL == dst)
    {
        dst = src;
    }
    SAFE_REF(shader);
    SAFE_REF(src);
    SAFE_REF(dst);
    mShader = shader;
    mSrc = src;
    mDst = dst;
}
GLBitmapWork::~GLBitmapWork()
{
}

bool GLBitmapWork::onPrepare()
{
    assert(NULL!=mSrc.get() && NULL!=mDst.get());
    GLAutoLock _l(mLock);
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
    GLAutoLock _l(mLock);
    /*Read result back from texture*/
    assert(NULL!=mDst.get());
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

void GLBitmapWork::set(GPPtr<GLBmp> src, GPPtr<GLBmp> dst)
{
    mSrc = src;
    mDst = dst;
    this->onSet();
}

class GLBitmapWork_Creater:public GLBitmapWorkCreater
{
    public:
        virtual GLBitmapWork* vCreate(std::istream* input) const
        {
            if (NULL == input)
            {
                return new GLBitmapWork;
            }
            std::istream& is = *input;
            std::ostringstream os;
            os << is.rdbuf();
            GPPtr<GLBitmapWork::Shader> s = new GLBitmapWork::Shader(os.str().c_str());
            return new GLBitmapWork(NULL, NULL, s.get());
        }
        virtual void vDetail(std::ostream& os) const
        {
            os <<"Usage: input stream was the fragment shader, default shader is below:"<<std::endl;
            os << gDefaultFrag <<std::endl;
        }
};

static GLBitmapWorkCreatorRegister<GLBitmapWork_Creater> __T("Basic");
