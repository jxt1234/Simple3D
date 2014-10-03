#ifndef FRAGMENT_GLLIGHTFUNCTION_H
#define FRAGMENT_GLLIGHTFUNCTION_H

#include "interface/IFragmentFunction.h"
#include "math/GLVector.h"

struct gl_MaterialParameters
{
    GLVector::vec4 emission;
    GLVector::vec4 ambient;
    GLVector::vec4 diffuse;
    GLVector::vec4 specular;
    GLVector::vec4 sceneColor;
    float shininess;
};

IRasterizatedVarying* GLSingleLightFunction(gl_MaterialParameters* m, GLVector::vec3 lightpos, GLVector::vec3 eyepos, IRasterizatedVarying* position, IRasterizatedVarying* normal, IRasterizatedVarying* basicColor);

#endif

