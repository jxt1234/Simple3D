#include "GL/GLCurveObject.h"
#include "GL/GLBiCubicCurveObj.h"
#include "GL/GLLightCurveObj.h"
#include "GL/GLCurveObjectFactory.h"
#include "utils/GLLock.h"
#include "math/BasicFunctionDeter.h"
#include <fstream>

IFunctionDeter* GLCurveObjectFactory::gDeter = NULL;

static GLLock gLock;

GLCurveObject* GLCurveObjectFactory::create(TYPE t)
{
    GLAutoLock _l(gLock);
    if (NULL == gDeter)
    {
        std::ifstream is("function.txt");//TODO
        gDeter = new BasicFunctionDeter(is);
        is.close();
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


