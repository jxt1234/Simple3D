#include "GL/GLvboBuffer.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

CONTEXT_API GLvboBuffer::GLvboBuffer(const float* buffer, int unit, int size, int type):mType(type)
{
    glGenBuffers(1, &mId);
    OPENGL_CHECK_ERROR;
    mUnit = unit;
    mSize = size;
    glBindBuffer(GL_ARRAY_BUFFER, mId);
    OPENGL_CHECK_ERROR;
    glBufferData(GL_ARRAY_BUFFER, size*unit*sizeof(GL_FLOAT), buffer, GL_STATIC_DRAW);
    OPENGL_CHECK_ERROR;
}

CONTEXT_API GLvboBuffer::GLvboBuffer(IVarying* buffer, int type):mType(type)
{
    glGenBuffers(1, &mId);
    OPENGL_CHECK_ERROR;
    mUnit = buffer->unit();
    mSize = buffer->size();
    float* tempBuffer = new float[mUnit*mSize];
    for (int i =0; i<mSize; ++i)
    {
        float* src = buffer->load(i);
        memcpy(tempBuffer+i*mUnit, src, mUnit*sizeof(float));
    }
    glBindBuffer(GL_ARRAY_BUFFER, mId);
    OPENGL_CHECK_ERROR;
    glBufferData(GL_ARRAY_BUFFER, mSize*mUnit*sizeof(GL_FLOAT), tempBuffer, GL_STATIC_DRAW);
    OPENGL_CHECK_ERROR;
    delete [] tempBuffer;
}


CONTEXT_API void GLvboBuffer::reset()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    OPENGL_CHECK_ERROR;
}

CONTEXT_API GLvboBuffer::~GLvboBuffer()
{
    glDeleteBuffers(1, &mId);
    OPENGL_CHECK_ERROR;
}

CONTEXT_API void GLvboBuffer::use(int id)
{
    GLASSERT(0!=mId);
    glEnableVertexAttribArray(id);
    OPENGL_CHECK_ERROR;
    glBindBuffer(GL_ARRAY_BUFFER, mId);
    OPENGL_CHECK_ERROR;
    glVertexAttribPointer(id, mUnit, GL_FLOAT, GL_FALSE, 0, NULL);
    OPENGL_CHECK_ERROR;
}

CONTEXT_API void GLvboBuffer::use(int id, int subUnit, int offset)
{
    GLASSERT(0!=mId);
    GLASSERT(subUnit<=mUnit);
    glEnableVertexAttribArray(id);
    OPENGL_CHECK_ERROR;
    glBindBuffer(GL_ARRAY_BUFFER, mId);
    OPENGL_CHECK_ERROR;
    glVertexAttribPointer(id, subUnit, GL_FLOAT, GL_FALSE, mUnit*sizeof(GL_FLOAT), reinterpret_cast<void*>(offset*sizeof(GL_FLOAT)));
    OPENGL_CHECK_ERROR;
}

CONTEXT_API void GLvboBuffer::update(float* subBuffer, int off, int len)
{
    GLASSERT(0!=mId);
    glBindBuffer(GL_ARRAY_BUFFER, mId);
    OPENGL_CHECK_ERROR;
    glBufferSubData(GL_ARRAY_BUFFER, off*mUnit*sizeof(float), len*mUnit*sizeof(float), subBuffer);
    OPENGL_CHECK_ERROR;
}

void GLvboBuffer::draw()
{
    glDrawArrays(mType, 0, mSize);
    OPENGL_CHECK_ERROR;
}

