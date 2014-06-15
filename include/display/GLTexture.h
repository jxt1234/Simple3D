#ifndef DISPLAY_TEXTURE_H
#define DISPLAY_TEXTURE_H
/*Basic GLTexture, has no mipmap and just support ARGB GLTexture*/
#include "head.h"

class GLTexture
{
    public:
        GLTexture();
        virtual ~GLTexture();
        CONTEXT_API virtual void init();
        CONTEXT_API void destory();
        CONTEXT_API void use();
        CONTEXT_API void use(int uniId, int texId);
        CONTEXT_API void upload(void* pixels, int w, int h);
        inline unsigned int id(){return mId;}
    protected:
        unsigned int mId;
};

#endif
