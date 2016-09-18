#ifndef ASSET_GLIASSET_H
#define ASSET_GLIASSET_H
#include "lowlevelAPI/GPStream.h"
class GLIAsset
{
public:
    virtual ~ GLIAsset(){}
    virtual void unFlatten(GPStream* input) = 0;
    virtual void flatten(GPWStream* output) = 0;
protected:
    GLIAsset(){}
};
#endif
