#ifndef GL_GLCONTEXT_H
#define GL_GLCONTEXT_H
class GLContext
{
public:
    class nativeContext;
    static nativeContext* init(int version=2);
    static void destroy(nativeContext* context);
};

class GLAutoContext
{
    public:
        GLAutoContext()
        {
            mContext = GLContext::init();
        }
        ~GLAutoContext()
        {
            GLContext::destroy(mContext);
        }
    private:
        GLContext::nativeContext* mContext;
};
#endif
