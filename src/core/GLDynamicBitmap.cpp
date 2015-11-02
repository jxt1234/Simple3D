#include "core/GLDynamicBitmap.h"
#include "utils/debug.h"

GLDynamicBitmap::GLDynamicBitmap(GPPtr<GLBmp> backgroud)
{
    GLASSERT(NULL!=backgroud.get());
    mBackGround = backgroud;
}
GLDynamicBitmap::~GLDynamicBitmap()
{
    
}
void GLDynamicBitmap::addFrames(GPPtr<GLBmp> frame, int l, int t)
{
    GLASSERT(frame.get()!=NULL);
    GLASSERT(frame->width() + l <= mBackGround->width());
    GLASSERT(frame->height() + t <= mBackGround->height());
    GLRect r;
    r.l = l;
    r.t = t;
    r.r = l+frame->width()-1;
    r.b = l+frame->height()-1;
    mDynamics.push_back(std::make_pair(frame, r));
}

void GLDynamicBitmap::clearFrames()
{
    mDynamics.clear();
}

void GLDynamicBitmap::render(GLBmp* display, size_t n, bool render_dirty) const
{
    GLASSERT(NULL!=display);
    GLASSERT(n<mDynamics.size());
    GLASSERT(display->width() == mBackGround->width());
    GLASSERT(display->height() == mBackGround->height());
    auto frame = mDynamics[n];
    int w = display->width();
    int h = display->height();
    if (!render_dirty)
    {
        int size = w*4;
        for(int i=0; i<h; ++i)
        {
            auto dst = display->getAddr(0, i);
            auto src = mBackGround->getAddr(0, i);
            ::memcpy(dst, src, size);
        }
    }
    auto rect = frame.second;
    int sw = rect.r-rect.l+1;
    for (int i=0; i<sw; ++i)
    {
        int size = sw*4;
        auto dst = display->getAddr(rect.l, rect.t+i);
        auto src = (frame.first)->getAddr(0, i);
        ::memcpy(dst, src, size);
    }
}
