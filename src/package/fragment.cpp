#include "package/fragment.h"
#include <assert.h>
#include "fragment/texture2D.h"
#include "fragment/GLWritePixels.h"

using namespace std;

static void fragment_free(void* s)
{
    IRasterizatedVarying* v = (IRasterizatedVarying*)s;
    delete v;
}


GP_Output GLPackageTexture2D(GP_Input inputs)
{
    assert(inputs.size()==2);
    IBitmap* s = (IBitmap*)inputs[0];
    IRasterizatedVarying* t = (IRasterizatedVarying*)inputs[1];
    GP_Output::GP_Unit result;
    result.content = texture2D(s, t);
    result.freeCallBack = fragment_free;
    GP_OUTPUT_SINGLE_EXIT(x, result);
}

GP_Output GLPackageWritePixels(GP_Input inputs)
{
    assert(inputs.size() == 3);
    /*Status*/
    IBitmap* dst = (IBitmap*)inputs[2];
    /*Inputs*/
    IRasterizatedVarying* pos = (IRasterizatedVarying*)inputs[0];
    IRasterizatedVarying* color = (IRasterizatedVarying*)inputs[1];
    GLWritePixels(dst, pos,color);
    GP_Output::GP_Unit result;
    result.content = dst;
    result.freeCallBack = NULL;
    GP_OUTPUT_SINGLE_EXIT(x, result);
}
GP_Output GLPackageSingleLight(GP_Input inputs)
{
    GP_Output::GP_Unit result;
    GP_OUTPUT_SINGLE_EXIT(x, result);
}
