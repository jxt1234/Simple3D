#ifndef GL_GLBICUBICWORK_H
#define GL_GLBICUBICWORK_H
#include "GLBitmapWork.h"
class GLBicubicWork:public GLTextureWork
{
    public:
        GLBicubicWork(float a);
        virtual ~GLBicubicWork();
        virtual void onUse(int proId, int srcW, int srcH);
        virtual bool onGenerateShader(std::ostream& vertex, std::ostream& frag) const;
    private:
        void _genShader(std::ostream& frag) const;
        float mA;
};
#endif
