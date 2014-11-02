#include "GL/GLTexture1Obj.h"

void GLTexture1Obj::set(GPPtr<GLTexture> t, GPPtr<GLvboBuffer> ver, GPPtr<GLvboBuffer> tex, GPPtr<GLvboBuffer> normal, int verId, int texId, int normaliId)
{
    GLASSERT(NULL!=t.get() && NULL!=ver.get() && NULL!=tex.get());

    mTexture = t;

    mVertex = ver;
    mTexCord = tex;
    mNormal = normal;

    mVerId = verId;
    mTexId = texId;
    mNormalId = normaliId;
}
GLTexture1Obj::GLTexture1Obj()
{
}
GLTexture1Obj::~GLTexture1Obj()
{
}

void GLTexture1Obj::onDraw(const GLMatrix4& transform, const GLMatrix4& view, const GLMatrix4& projection)
{
    mTexture->use();
    mVertex->use(mVerId);
    mTexCord->use(mTexId);
    mNormal->use(mNormalId);
    mVertex->draw();
}
