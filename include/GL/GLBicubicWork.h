#ifndef GL_GLBICUBICWORK_H
#define GL_GLBICUBICWORK_H
#include "GLBitmapWork.h"
class GLBicubicWork:public GLTextureWork
{
    public:
        GLBicubicWork(float a);
        virtual ~GLBicubicWork();
        virtual bool onGenerateShader(std::ostream& vertex, std::ostream& frag) const;
        virtual void onUse(GLTexture* dst, std::vector<GLTexture*> sources, GLProgram* shader);
    private:
        void _genShader(std::ostream& frag) const;
        float mA;
};
#endif
