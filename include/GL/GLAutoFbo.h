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
};
