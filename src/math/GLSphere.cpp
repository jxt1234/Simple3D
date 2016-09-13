#include "math/GLSphere.h"
#include <math.h>
#include "utils/GLDebug.h"
#define PI 3.141592653

using namespace GLVector;

void GLSphere::pos(float* out, float u, float v)
{
    u=2*u;
    v=v-0.5;
    out[0] = r*cos(u*PI)*cos(v*PI);
    out[1] = r*sin(u*PI)*cos(v*PI);
    out[2] = r*sin(v*PI/2.0);
    add(out, out, m, 3);
}
void GLSphere::normal(float* out, float u, float v)
{
    u=2*u;
    v=v-0.5;
    out[0] = r*cos(u*PI)*cos(v*PI);
    out[1] = r*sin(u*PI)*cos(v*PI);
    out[2] = r*sin(v*PI);
}
