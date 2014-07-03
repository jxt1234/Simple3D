#ifndef DISPLAY_TEXTURE_H
#define DISPLAY_TEXTURE_H
/*Basic GLTexture, has no mipmap and just support ARGB GLTexture*/
#include "head.h"
#include "utils/RefCount.h"
class CONTEXT_CLASS GLTexture:public RefCount
{
    public:
        GLTexture();
        virtual ~GLTexture();
        void use();
        void use(int uniId, int texId);
        /*Only support RGBA*/
        CONTEXT_API void upload(void* pixels, int w, int h);
        inline unsigned int id(){return mId;}
    protected:
        void init();
        void destory();
    private:
        unsigned int mId;
};

#endif
