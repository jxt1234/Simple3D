#ifndef GL_GLAUTOFBO_H
#define GL_GLAUTOFBO_H
#include "head.h"
#include "GLTexture.h"
/*TODO Support MRT*/
CONTEXT_CLASS class GLAutoFbo
{
public:
    GLAutoFbo(GLTexture& dst);
    ~GLAutoFbo();
private:
    unsigned int mId;
    unsigned int mPrevious;
    int mViewPort[4];
    int mEnableClip;
    
};
#endif
