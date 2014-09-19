#include "utils/RefCount.h"

class GLWork:public RefCount
{
    public:
        /*Run in GL Thread*/
        virtual bool onPrepare() = 0;//Create Shader, copy data to texture
        virtual void onProcess() = 0;//Run (In most case, glDrawArray)
        virtual void onFinish() = 0;//Destroy shader if needed, Copy texture to dstData

        /*Run in other Thread*/

        GLWork(){}
        virtual ~GLWork(){}
};

