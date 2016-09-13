#include "user/GPStream.h"

class GLIAsset
{
public:
    virtual ~ GLIAsset(){}
    virtual void unFlatten(GPStream* input) = 0;
    virtual void flatten(GPWStream* output) = 0;
protected:
    GLIAsset(){}
};