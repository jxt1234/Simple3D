#ifndef GL_GLTEXTUREMATRIXWORK_H
#define GL_GLTEXTUREMATRIXWORK_H
#include "GLTextureWork.h"
#include "math/GLMatrix4.h"
class GLTextureMatrixWork:public GLTextureWork
{
    public:
        GLTextureMatrixWork(const GLMatrix4& matrix);
        virtual ~GLTextureMatrixWork();
        virtual void onUse(GLTexture* dst, std::vector<GLTexture*> sources, GLProgram* shader);
    private:
        GLMatrix4 mMatrix;
};
#endif
