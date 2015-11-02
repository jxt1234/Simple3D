#ifndef CORE_GLDYNAMICBITMAP_H
#define CORE_GLDYNAMICBITMAP_H
#include "GLBmp.h"
#include "GLRect.h"
#include <vector>
class GLDynamicBitmap:public RefCount
{
public:
    GLDynamicBitmap(GPPtr<GLBmp> backgroud);
    virtual ~GLDynamicBitmap();
    void addFrames(GPPtr<GLBmp> frame, int l, int t);
    void clearFrames();
    void render(GLBmp* display, size_t n, bool render_dirty) const;
    inline int width() const {return mBackGround->width();}
    inline int height() const {return mBackGround->height();}
    
    inline size_t getFrames() const {return mDynamics.size();}
private:
    GPPtr<GLBmp> mBackGround;
    std::vector<std::pair<GPPtr<GLBmp>, GLRect>> mDynamics;
};
#endif
