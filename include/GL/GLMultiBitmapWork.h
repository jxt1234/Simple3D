#include "GLTextureWork.h"
#include "GLBitmapWork.h"
#include <vector>

CONTEXT_CLASS class GLMultiBitmapWork:public GLWork
{
    public:
        GLMultiBitmapWork(GPPtr<GLBmp> dst);
        virtual ~GLMultiBitmapWork();

        void addWork(GPPtr<GLTextureWork> work, GPPtr<GLBmp> src);
        virtual void onProcess();
        virtual bool onPrepare()
        {
            return true;
        }
        virtual void onFinish()
        {
        }
        virtual void onDestroy()
        {
        }
    private:
        GPPtr<GLBmp> mDst;
        std::vector<std::pair<GPPtr<GLTextureWork>, GPPtr<GLBmp>>> mWorks;
};
