#include "GL/GLContext.h"
#include <assert.h>

#ifdef GL_BUILD_FOR_ANDROID
#include <EGL/egl.h>
class GLContext::nativeContext
{
    public:
        nativeContext()
        {
            gDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
            EGLint majorVersion;
            EGLint minorVersion;
            eglInitialize(gDisplay, &majorVersion, &minorVersion);
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
            eglChooseConfig(gDisplay, configAttribs, &surfaceConfig, 1, &numConfigs);

            static const EGLint contextAttribs[] = {
                EGL_CONTEXT_CLIENT_VERSION, 2,
                EGL_NONE
            };
            gContext = eglCreateContext(gDisplay, surfaceConfig, NULL, contextAttribs);


            static const EGLint surfaceAttribs[] = {
                EGL_WIDTH, 1,
                EGL_HEIGHT, 1,
                EGL_NONE
            };
            gSurface = eglCreatePbufferSurface(gDisplay, surfaceConfig, surfaceAttribs);
            eglMakeCurrent(gDisplay, gSurface, gSurface, gContext);
        }
    ~nativeContext()
    {
        eglMakeCurrent(gDisplay, EGL_NO_SURFACE , EGL_NO_SURFACE , EGL_NO_CONTEXT);
        eglDestroyContext(gDisplay, gContext);
        eglDestroySurface(gDisplay, gSurface);
        eglTerminate(gDisplay);
        gDisplay = EGL_NO_DISPLAY;
    }
 
    private:
        EGLContext gContext;
        EGLDisplay gDisplay;
        EGLSurface gSurface;
};
#else
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
class GLContext::nativeContext
{
    public:
        nativeContext()
        {
            CGLPixelFormatAttribute attributes[] = {
                kCGLPFADoubleBuffer,
                (CGLPixelFormatAttribute)0
            };
            CGLPixelFormatObj pixFormat;
            GLint npix;

            CGLChoosePixelFormat(attributes, &pixFormat, &npix);
            assert(NULL!=pixFormat);

            CGLCreateContext(pixFormat, NULL, &gContext);
            CGLReleasePixelFormat(pixFormat);
            assert(NULL!=gContext);
            CGLSetCurrentContext(gContext);
        }
        ~nativeContext()
        {
            CGLReleaseContext(gContext);
        }
    private:
        CGLContextObj gContext;
};
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
class GLContext::nativeContext
{
    public:
        nativeContext()
        {
            gDisplay = XOpenDisplay(0);
            int fbcount;
            static int visual_attribs[] = {
                GLX_X_RENDERABLE    , True,
                GLX_DRAWABLE_TYPE   , GLX_PIXMAP_BIT,
                None
            };
            GLXFBConfig *fbc = glXChooseFBConfig(gDisplay, DefaultScreen(gDisplay),
                    visual_attribs, &fbcount);
            int best_fbc = -1, best_num_samp = -1;

            int i;
            for (i = 0; i < fbcount; ++i) {
                XVisualInfo *vi = glXGetVisualFromFBConfig(gDisplay, fbc[i]);
                if (vi) {
                    int samp_buf, samples;
                    glXGetFBConfigAttrib(gDisplay, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
                    glXGetFBConfigAttrib(gDisplay, fbc[i], GLX_SAMPLES, &samples);
                    if (best_fbc < 0 || (samp_buf && samples > best_num_samp))
                        best_fbc = i, best_num_samp = samples;
                }
                XFree(vi);
            }
            GLXFBConfig bestFbc = fbc[best_fbc];
            XFree(fbc);
            XVisualInfo *vi = glXGetVisualFromFBConfig(gDisplay, bestFbc);
            gPixmap = XCreatePixmap(gDisplay, RootWindow(gDisplay, vi->screen), 10, 10, vi->depth);
            gGlxPixmap = glXCreateGLXPixmap(gDisplay, vi, gPixmap);
            XFree(vi);
            gContext = glXCreateNewContext(gDisplay, bestFbc, GLX_RGBA_TYPE, 0, True);
            glXMakeCurrent(gDisplay, gGlxPixmap, gContext);
            glewInit();
        }
        ~nativeContext()
        {
            glXMakeCurrent(gDisplay, 0,0);
            glXDestroyContext(gDisplay, gContext);
            glXDestroyGLXPixmap(gDisplay, gGlxPixmap);
            XFreePixmap(gDisplay, gPixmap);
            XCloseDisplay(gDisplay);
            gDisplay = NULL;
        }
    private:
        GLXContext gContext;
        Pixmap gPixmap;
        GLXPixmap gGlxPixmap;
        Display* gDisplay;
};
#endif
#endif


GLContext::nativeContext* GLContext::init(int version)
{
    return new nativeContext;
}

void GLContext::destroy(nativeContext* context)
{
    delete context;
}
