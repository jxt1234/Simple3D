#include "utils/RefCount.h"

class GLWork:public RefCount
{
    public:
        /*Run in GL Thread*/
        virtual bool onPrepare() = 0;//Create Shader, copy data to texture if needed
        virtual void onProcess() = 0;//Run (In most case, glDrawArray)
        virtual void onFinish() = 0;//After this work is done, copy result if needed
        virtual void onDestroy() = 0;;//destroy resource

        void runOnePass()
        {
            this->onPrepare();
            this->onProcess();
            this->onFinish();
            this->onDestroy();
        }

        /*Run in other Thread*/

        GLWork(){}
        virtual ~GLWork(){}
};

