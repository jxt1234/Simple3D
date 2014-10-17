#include "test/GLTest.h"
#include "GL/GLMixWork.h"
#include "GL/GLBitmapWorkFactory.h"
#include "GL/GLAutoFbo.h"

class GLMixFractionTest:public GLTest
{
    public:
        virtual void run();
        GLMixFractionTest(){}
        virtual ~GLMixFractionTest(){}
};

void GLMixFractionTest::run()
{
    GPPtr<GLBmp> src = new GLBmp("input2.jpg");
    int w = src->width();
    int h = src->height();
    GPPtr<GLBmp> dst = new GLBmp(w, h);

    {
        GPPtr<GLTexture> frac = new GLTexture;
        frac->upload(NULL, w, h);
        GPPtr<GLTexture> result = new GLTexture;
        result->upload(NULL, w, h);
        GPPtr<GLTexture> srcT = new GLTexture;
        srcT->upload(src->pixels(), w, h);
        std::vector<GLTexture*> _source(1, srcT.get());
        {
            GPPtr<GLBitmapWork> work = GLBitmapWorkFactory::create("Fraction");
            GPPtr<GLTextureWork> _tw = work->work();
            _tw->onPrepare();
            _tw->run(frac.get(), _source);
            _tw->onDestroy();
        }

        _source.push_back(frac.get());
        {
            GPPtr<GLBitmapWork> work = GLBitmapWorkFactory::create("MixBitmap");
            GPPtr<GLTextureWork> _tw = work->work();
            _tw->onPrepare();
            _tw->run(result.get(), _source);
            _tw->onDestroy();
        }
        {
            GLAutoFbo __F(*result);
            result->download(dst->pixels());
        }
    }
    dst->save("output/GLMixFractionTest.png");
}
static GLTestRegister<GLMixFractionTest> a("GLMixFractionTest");
