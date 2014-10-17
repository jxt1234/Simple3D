#ifndef GL_GLMULTIPASSWORK_H
#define GL_GLMULTIPASSWORK_H
#include "GLTextureWork.h"
class GLMultiPassWork:public GLTextureWork
{
    public:
        GLMultiPassWork();
        virtual ~GLMultiPassWork();
        virtual void run(GLTexture* dst, std::vector<GLTexture*> sources);
    private:
        virtual int vGetStep() const = 0;
        virtual bool vCurrent(GLProgram** program) const = 0;//If return NULL, means reach end
        virtual void vNext() = 0;
        virtual void vRewind() = 0;
        typedef GLTextureWork INHERIT;
};
#endif
