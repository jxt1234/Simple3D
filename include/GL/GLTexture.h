#ifndef DISPLAY_TEXTURE_H
#define DISPLAY_TEXTURE_H
/*Basic GLTexture, has no mipmap and just support ARGB GLTexture*/
#include "head.h"
#include "utils/RefCount.h"
class CONTEXT_CLASS GLTexture:public RefCount
{
public:
    typedef enum{
        RGBA,
        RGB_565,
        ALPHA
    } Format;
    GLTexture(int target = GL_TEXTURE_2D);
    //Already Has Texture, just wrap it
    GLTexture(int id, int w, int h, int target = GL_TEXTURE_2D);
    virtual ~GLTexture();
    void use();
    void use(int uniId, int texId);
    void setFilter(bool filter);
    inline int width() const {return mW;}
    inline int height() const {return mH;}
    /*Only support RGBA*/
    CONTEXT_API void upload(void* pixels, int w, int h);
    CONTEXT_API void uploadAllFormat(void* pixels, int w, int h, int stride, Format format);
    CONTEXT_API void download(void* pixels);
    inline unsigned int id() const{return mId;}
    inline int target() const {return mTarget;}
    void reset();
protected:
    void init();
    void destory();
private:
    unsigned int mId;
    int mW;
    int mH;
    int mTarget;
    bool mWarp;
};

#endif
