#include "GL/GLCamera.h"
GLCamera::GLCamera(int w, int h):mWidth(w), mHeight(h)
{
    mPos[0] = 0;
    mPos[1] = 0;
    mPos[2] = -1;

    mNear = 0.1;
    mSeta = 60;
    invalidate();
}

GLCamera::~GLCamera()
{
}

void GLCamera::invalidate()
{
}
