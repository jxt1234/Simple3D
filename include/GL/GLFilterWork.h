#ifndef GL_GLFILTERWORK_H
#define GL_GLFILTERWORK_H
#include "GLMultiPassWork.h"
class GLFilterWork:public GLMultiPassWork
{
    public:
        GLFilterWork(GLBmp* src, GLBmp* dst, const float* p=NULL, int n=0);
        virtual ~GLFilterWork();

        virtual void onSet(GPPtr<GLBmp> src, GPPtr<GLBmp> dst);
    private:
        void _buildShaders();
        static void _genShader(std::ostream& os, const float* p, int n, float xOffset, float yOffset);

        float* mP;
        int mN;
};
#endif
