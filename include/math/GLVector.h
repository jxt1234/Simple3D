#ifndef CORE_GLVECTOR_H
#define CORE_GLVECTOR_H

namespace GLVector
{
typedef float vec3[3];
typedef float vec4[4];

void setVec4(float x, float y, float z, float w, float* out);
void setVec3(float x, float y, float z, float* out);

float model(float* v, int n);


void equal(float* out, float* in, int n);
void reverse(float* out, float* in, int n);
void normalize(float* v);
float dot(float* v1, float* v2);
void cross(float* out, float* v1, float* v2);
void reflect(float* out, float* L, float* N);
void scale(float* v, float p, int n);
float max(float a, float b);



void multi(float* out, float* v1, float* v2, int n);
void add(float* out, float* v1, float* v2, int n);
void minus(float* out, float* v1, float* v2, int n);
void linear(float* out, float* v1, float p1, float* v2, float p2, int n);




};


#endif
