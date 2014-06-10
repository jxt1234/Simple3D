#ifndef FRAGMENT_GLLIGHTFUNCTION_H
#define FRAGMENT_GLLIGHTFUNCTION_H

#include "interface/IFragmentFunction.h"
#include "math/GLVector.h"

struct gl_MaterialParameters
{
    vec4 emission;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 sceneColor;
    float shininess;
};

IRasterizatedVarying* GLSingleLightFunction(gl_MaterialParameters* m, vec3 lightpos, vec3 eyepos, IRasterizatedVarying* position, IRasterizatedVarying* normal, IRasterizatedVarying* basicColor);

#endif

