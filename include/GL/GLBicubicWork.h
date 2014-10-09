#include "GLBitmapWork.h"
class GLBicubicWork:public GLBitmapWork
{
    public:
        GLBicubicWork(float a);
        virtual ~GLBicubicWork();
        virtual void onSet();

    private:
        void _genShader(std::ostream& frag, int w, int h);

        float mA;
};
