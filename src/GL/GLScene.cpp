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
void GLScene::onDraw(const GLMatrix4& transform, const GLMatrix4& projection)
{
    GLMatrix4 curTransform = (mTransformer->get())*transform;
    this->vRewind();
    while(!this->vEnd())
    {
        GPPtr<GLObject> o = this->vCurrent();
        o->onDraw(curTransform, projection);
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

