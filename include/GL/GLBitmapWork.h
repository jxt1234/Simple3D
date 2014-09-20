#include "head.h"
#include "GLWork.h"
#include "GLProgram.h"
#include "GLTexture.h"
#include "core/GLBmp.h"

/*This kind of work run glsl from src to dst, if dst is NULL, then it write result to src*/
class GLBitmapWork:public GLWork
{
    public:
        class Shader:public RefCount
        {
            public:
                Shader(const char* fragSource = NULL, bool xlinear = false, bool ylinear = false, bool mipmiap = false, bool repeat = false);
                ~Shader();
                /*Return mProgram's id*/
                int setUp();
                const GLProgram& program() const {return mProgram;}
            private:
                GLProgram mProgram;
                bool mValid;

        };

        GLBitmapWork(GLBmp* src, GLBmp* dst=NULL, Shader* shader = NULL);
        GLBitmapWork(GLTexture* src, GLTexture* dst, Shader* shader = NULL);
        ~GLBitmapWork();

        virtual bool onPrepare();
        virtual void onProcess();
        virtual void onFinish();
    private:
        GLBmp* mSrc;
        GLBmp* mDst;

        GLTexture* mSrcT;
        GLTexture* mDstT;

        Shader* mShader;
};
