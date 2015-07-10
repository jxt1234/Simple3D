#ifndef GL_GLCONTEXT_H
#define GL_GLCONTEXT_H
class GLContext
{
public:
    static bool init(int version=2);
    static void destroy();
};
#endif
