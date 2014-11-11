#include "GL/GLCurveObject.h"
#include "GL/GLBiCubicCurveObj.h"
#include "GL/GLLightCurveObj.h"
#include "GL/GLCurveObjectFactory.h"
#include "utils/GLLock.h"
#include "math/BasicFunctionDeter.h"
#include "AllShader.h"
#include <sstream>

IFunctionDeter* GLCurveObjectFactory::gDeter = NULL;

static GLLock gLock;

GLCurveObject* GLCurveObjectFactory::create(TYPE t)
{
    GLAutoLock _l(gLock);
    if (NULL == gDeter)
    {
        std::istringstream is(glsl_function_txt_vex);
        gDeter = new BasicFunctionDeter(is);
    }
    GLCurveObject* res = NULL;
    switch (t)
    {
        case NONE:
            res = new GLCurveObject;
            break;
        case LIGHT:
            res = new GLLightCurveObj(gDeter);
            break;
        case BICUBIC:
            res = new GLBiCubicCurveObj;
            break;
        default:
            break;
    }
    return res;
}


