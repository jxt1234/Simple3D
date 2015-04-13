#include "GL/GLContext.h"
#ifdef GL_BUILD_FOR_ANDROID
#include <EGL/egl.h>
static EGLContext fContext;
static EGLDisplay fDisplay;
static EGLSurface fSurface;
bool GLContext::init(int version)
{
    fDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    EGLint majorVersion;
    EGLint minorVersion;
    eglInitialize(fDisplay, &majorVersion, &minorVersion);
    EGLint numConfigs;
    static const EGLint configAttribs[] = {
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_NONE
    };

    EGLConfig surfaceConfig;
    eglChooseConfig(fDisplay, configAttribs, &surfaceConfig, 1, &numConfigs);

    static const EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, version,
        EGL_NONE
    };
    fContext = eglCreateContext(fDisplay, surfaceConfig, NULL, contextAttribs);


    static const EGLint surfaceAttribs[] = {
            EGL_WIDTH, 1,
            EGL_HEIGHT, 1,
            EGL_NONE
        };
    fSurface = eglCreatePbufferSurface(fDisplay, surfaceConfig, surfaceAttribs);
    eglMakeCurrent(fDisplay, fSurface, fSurface, fContext);
    return true;
}

//TODO
void GLContext::destroy()
{
}
#elifdef GL_BUILD_FOR_UBUNTU
#include <GL/glew.h>
#include <GL/glut.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
static GLXContext fContext;
static Pixmap fPixmap;
static GLXPixmap fGlxPixmap;
static Display* fDisplay = XOpenDisplay(0);
bool GLContext::init(int version)
{
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
    return true;
}

//TODO
void GLContext::destroy()
{
}
#else
bool GLContext::init(int version)
{
    return true;
}
void GLContext::destroy()
{
    
}
#endif
