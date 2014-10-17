#ifndef GL_GLFILTERWORK_H
#define GL_GLFILTERWORK_H
#include "GLMultiPassWork.h"
class GLFilterWork:public GLMultiPassWork
{
    public:
        GLFilterWork(const float* p=NULL, int n=0);
        virtual ~GLFilterWork();

        virtual bool onGenerateShader(std::ostream& vertex, std::ostream& frag) const;
    protected:
        virtual void onUse(GLTexture* dst, std::vector<GLTexture*> sources, GLProgram* shader);
    private:
        int vGetStep() const {return 2;}
        bool vCurrent(GLProgram** program) const;
        virtual void vNext();
        virtual void vRewind();
        static void _genShader(std::ostream& os, const float* p, int n);

        float* mP;
        int mN;

        int mPass;
};
#endif
