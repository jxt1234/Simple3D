#include "math/GLVector.h"
#include <math.h>

namespace GLVector
{

void setVec4(float x, float y, float z, float w, float* out)
{
    out[0] = x;
    out[1] = y;
    out[2] = z;
    out[3] = w;
}

float model(float* v, int n)
{
    float r = sqrt(v[0]*v[0] + v[1]*v[1]+v[2]*v[2]);
    return r;
}

void setVec3(float x, float y, float z, float* out)
{
    out[0] = x;
    out[1] = y;
    out[2] = z;
}

void equal(float* out, float* in, int n)
{
    for (int i=0; i<n; ++i)
    {
        out[i] = in[i];
    }
}
void reverse(float* out, float* in, int n)
{
    for (int i=0; i<n; ++i)
    {
        out[i] = -in[i];
    }
}
void normalize(float* v)
{
    float r = sqrt(v[0]*v[0] + v[1]*v[1]+v[2]*v[2]);
    v[0]/=r;
    v[1]/=r;
    v[2]/=r;
}

float max(float a, float b)
{
    if (a > b) return a;
    return b;
}


float dot(float* v1, float* v2)
{
    float result = v1[0]*v2[0] + v1[1]*v2[1]+v1[2]*v2[2];
    return result;
}

void cross(float* out, float* v1, float* v2)
{
    out[0] = v1[1]*v2[2]-v1[2]*v2[1];
    out[1] = v1[2]*v2[0]-v1[0]*v2[2];
    out[2] = v1[0]*v2[1]-v1[1]*v2[0];
}

void multi(float* out, float* v1, float* v2, int n)
{
    for (int i=0; i<n; ++i)
        out[i] = v1[i]*v2[i];
}

void scale(float* v, float p, int n)
{
    for (int i=0; i<n; ++i)
        v[i] = v[i] * p;
}

void add(float* out, float* v1, float* v2, int n)
{
    for (int i=0; i<n; ++i)
        out[i] = v1[i]+v2[i];
}

void linear(float* out, float* v1, float p1, float* v2, float p2, int n)
{
    for (int i=0; i<n; ++i)
        out[i] = v1[i]*p1+v2[i]*p2;
}
void minus(float* out, float* v1, float* v2, int n)
{
    for (int i=0; i<n; ++i)
        out[i] = v1[i]-v2[i];
}
void reflect(float* out, float* L, float* N)
{
    float _cos = dot(L, N);
    out[0] = -L[0] + 2*N[0]*_cos;
    out[1] = -L[1] + 2*N[1]*_cos;
    out[2] = -L[2] + 2*N[2]*_cos;
    normalize(out);
}
};
