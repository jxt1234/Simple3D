#ifndef GL_GLMIXWORK_H
#define GL_GLMIXWORK_H
#include "GLTextureWork.h"
class GLMixWork:public GLTextureWork
{
    public:
        GLMixWork();
        virtual ~GLMixWork();
        virtual bool onGenerateShader(std::ostream& vertex, std::ostream& frag) const;
        virtual void onUse(GLTexture* dst, std::vector<GLTexture*> sources, GLProgram* shader);
};
#endif
