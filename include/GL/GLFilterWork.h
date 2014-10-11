#ifndef GL_GLFILTERWORK_H
#define GL_GLFILTERWORK_H
#include "GLMultiPassWork.h"
class GLFilterWork:public GLMultiPassWork
{
    public:
        GLFilterWork(const float* p=NULL, int n=0);
        virtual ~GLFilterWork();

        virtual bool onGenerateShader(std::ostream& vertex, std::ostream& frag) const;
    private:
        virtual bool vFinish() const;
        virtual void vNext();
        static void _genShader(std::ostream& os, const float* p, int n, float xOffset, float yOffset);

        float* mP;
        int mN;

        int mPass;
};
#endif
