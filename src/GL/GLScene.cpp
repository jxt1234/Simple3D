#include "GL/GLScene.h"
GLScene::GLScene()
{
    mTransformer = new GLTransformer;
}
GLScene::GLScene(GPPtr<GLTransformer> t)
{
    assert(NULL!=t.get());
    mTransformer = t;
}
GLScene::~GLScene()
{
}
void GLScene::onDraw(const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P)
{
    GLMatrix4 curTransform = (mTransformer->get())*M;
    this->vRewind();
    while(!this->vEnd())
    {
        GPPtr<GLObject> o = this->vCurrent();
        o->onDraw(curTransform, V, P);
        this->vNext();
    }
}

void GLScene::onPrepare()
{
    this->vRewind();
    while(!this->vEnd())
    {
        GPPtr<GLObject> o = this->vCurrent();
        o->onPrepare();
        this->vNext();
    }
}

