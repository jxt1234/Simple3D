#include "utils/debug.h"
class GLColorTable_GPType:public IStatusType
{
    public:
        GLColorTable_GPType():IStatusType("GLColorTable"){}
        virtual void* vLoad(GPStream* input) const
        {
            return NULL;
        }
        virtual void vSave(void* contents, GPWStream* output) const
        {
        }
        virtual void vFree(void* contents) const
        {
            GLColorTable* c = (GLColorTable*)contents;
            c->decRef();
        }
        virtual int vMap(void** content, double* value) const
        {
            int mapnumber=256*3;
            if (NULL == value || NULL == content)
            {
                return mapnumber;
            }
            if (NULL == *content)
            {
                *content = (void*)(new GLBmp(256, 1));
            }
            GLBmp* t = (GLBmp*)(*content);
            for (int i=0; i<256; ++i)
            {
                auto _t = t->getAddr(i, 0);
                for (int j=0; j<3; ++j)
                {
                    int v = i + (50*value[i*3+j]-0.5);
                    v = v>255?255:v;
                    v = v<0?0:v;
                    _t[j] = v;
                }
            }
            return mapnumber;
        }
};
