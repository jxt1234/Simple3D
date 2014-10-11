#ifndef GL_GLTEXTURE1OBJ_H
#define GL_GLTEXTURE1OBJ_H
#include "GLObject.h"
#include "GLTexture.h"
#include "GLvboBuffer.h"
class CONTEXT_CLASS GLTexture1Obj:public GLObject
{
    public:
        GLTexture1Obj(GPPtr<GLObject> basic);
        void set(GPPtr<GLTexture> t, GPPtr<GLvboBuffer> ver, GPPtr<GLvboBuffer> tex, GPPtr<GLvboBuffer> normal, int verId, int texId, int normaliId);
        virtual ~GLTexture1Obj();
        virtual void onPrepare(){}
        virtual void onDraw(const GLMatrix4& transform, const GLMatrix4& view, const GLMatrix4& projection);
    private:
        GPPtr<GLTexture> mTexture;
        GPPtr<GLvboBuffer> mVertex;
        GPPtr<GLvboBuffer> mTexCord;
        GPPtr<GLvboBuffer> mNormal;
        GPPtr<GLObject> mBasic;
        int mVerId;
        int mTexId;
        int mNormalId;
};
#endif
