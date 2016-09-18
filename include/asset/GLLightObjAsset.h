#ifndef ASSET_GLLIGHTOBJASSET_H
#define ASSET_GLLIGHTOBJASSET_H
#include "GLIAsset.h"
class GLLightObjAsset : public GLIAsset
{
public:
    GLLightObjAsset();
    virtual ~ GLLightObjAsset();
    
    virtual void unFlatten(GPStream* input) override;
    virtual void flatten(GPWStream* output) override;
    
    struct Point
    {
        double Vertex[3];
        unsigned char Color[3];
        double Normal[3];
        double Tangent[3];
        double UV[2];
    };
private:
    int mPointNumber = 0;
    Point* mPoints = NULL;
};
#endif
