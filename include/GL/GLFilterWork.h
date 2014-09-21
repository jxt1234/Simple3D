#include "GLMultiPassWork.h"

class GLFilterWork:public GLMultiPassWork
{
    public:
        GLFilterWork(GLBmp* src, GLBmp* dst);//TODO Support a matrix
        virtual ~GLFilterWork();
    private:
        static void _genShader(std::ostream& os, const float* p, int n, float xOffset, float yOffset);
};
