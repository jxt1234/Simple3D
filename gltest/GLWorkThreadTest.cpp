#include "test/GLTest.h"
#include "core/GLBmp.h"
#include "GL/GLBitmapWorkFactory.h"
#include "GL/GLBitmapWork.h"
#include "GL/GLWorkThread.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

class GLWorkThreadTest:public GLTest
{
    public:
        virtual void run();
        GLWorkThreadTest(){}
        virtual ~GLWorkThreadTest(){}
};

void create()
{
    GLXContext fContext;
    Display* fDisplay = XOpenDisplay(0);
    Pixmap fPixmap;
    GLXPixmap fGlxPixmap;
    int fbcount;
    static int visual_attribs[] = {
        GLX_X_RENDERABLE    , True,
        GLX_DRAWABLE_TYPE   , GLX_PIXMAP_BIT,
        None
    };
    GLXFBConfig *fbc = glXChooseFBConfig(fDisplay, DefaultScreen(fDisplay),
            visual_attribs, &fbcount);
    int best_fbc = -1, best_num_samp = -1;

    int i;
    for (i = 0; i < fbcount; ++i) {
        XVisualInfo *vi = glXGetVisualFromFBConfig(fDisplay, fbc[i]);
        if (vi) {
            int samp_buf, samples;
            glXGetFBConfigAttrib(fDisplay, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
            glXGetFBConfigAttrib(fDisplay, fbc[i], GLX_SAMPLES, &samples);
            if (best_fbc < 0 || (samp_buf && samples > best_num_samp))
                best_fbc = i, best_num_samp = samples;
        }
        XFree(vi);
    }
    GLXFBConfig bestFbc = fbc[best_fbc];
    XFree(fbc);
    XVisualInfo *vi = glXGetVisualFromFBConfig(fDisplay, bestFbc);
    fPixmap = XCreatePixmap(fDisplay, RootWindow(fDisplay, vi->screen), 10, 10, vi->depth);
    fGlxPixmap = glXCreateGLXPixmap(fDisplay, vi, fPixmap);
    XFree(vi);
    fContext = glXCreateNewContext(fDisplay, bestFbc, GLX_RGBA_TYPE, 0, True);
    glXMakeCurrent(fDisplay, fGlxPixmap, fContext);
    glewInit();
}
void GLWorkThreadTest::run()
{
    GLWorkThread worker(create, NULL);
    worker.start();
    GPPtr<GLBmp> src = new GLBmp("input2.jpg");
    GPPtr<GLBmp> dst = new GLBmp(720,1280);
    GLBitmapWork* work = GLBitmapWorkFactory::create("Fraction");
    assert(NULL!=work);
    GPPtr<GLWork> w = work;

    work->set(dst, dst);
    GPPtr<GLWorkSemore> s = worker.queueWork(w);
    s->wait();
    dst->save("output/GLWorkThreadTest.png");
    worker.stop();
}
static GLTestRegister<GLWorkThreadTest> a("GLWorkThreadTest");
