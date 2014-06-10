#ifndef CORE_GLDEPTHBUFFER_H
#define CORE_GLDEPTHBUFFER_H

class GLFloatBuffer
{
    public:
        GLFloatBuffer(int w, int h);
        virtual ~GLFloatBuffer();
    protected:
        float* addr(int x, int y);
        float* mBuffer;
        int mWidth;
        int mHeight;
};

/*The GLDepthFunc is fixed as GL_LESS*/
class GLDepthBuffer:public GLFloatBuffer
{
    public:
        GLDepthBuffer(int w, int h);
        virtual ~GLDepthBuffer(){}
        void reset();
        bool valid(float z, int x, int y);
};


#endif
