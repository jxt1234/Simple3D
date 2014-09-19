#include "head.h"
#include "GLWork.h"
#include "GLProgram.h"

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
            private:
                GLProgram mProgram;

        };
        GLBitmapWork(GLBitmapWorkShader* shader, GLBmp* src, GLBmp* dst=NULL);
        GLBitmapWork(GLBitmapWorkShader* shader, GLTexture* src, GLTexture* dst);
        ~GLBitmapWork();

        virtual bool onPrepare();
        virtual void onProcess();
        virtual void onFinish();
    private:
        GLBmp* mSrc;
        GLBmp* mDst;

        GLTexture* mSrcT;
        GLTexture* mDstT;
};
