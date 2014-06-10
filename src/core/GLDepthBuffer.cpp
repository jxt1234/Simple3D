#include "core/GLDepthBuffer.h"
#include <assert.h>

GLFloatBuffer::GLFloatBuffer(int w, int h)
{
    mBuffer = new float[w*h];
    mWidth = w;
    mHeight = h;
}

GLFloatBuffer::~GLFloatBuffer()
{
    delete [] mBuffer;
}

float* GLFloatBuffer::addr(int x, int y)
{
    return (mBuffer+x+y*mWidth);
}

GLDepthBuffer::GLDepthBuffer(int w, int h):GLFloatBuffer(w, h)
{
    reset();
}

bool GLDepthBuffer::valid(float z, int x, int y)
{
    /*TODO delete assert for speed*/
    assert(x>=0 && x<mWidth);
    assert(y>=0 && y<mHeight);
    float* p = addr(x, y);
    bool result = false;
    if (z<*p)
    {
        *p  = z;
        result = true;
    }
    return result;
}

void GLDepthBuffer::reset()
{
    for (int i=0; i<mWidth*mHeight; ++i)
    {
        mBuffer[i] = 1;
    }
}
