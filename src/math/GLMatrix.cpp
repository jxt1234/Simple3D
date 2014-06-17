#include "math/GLMatrix4.h"
#include <sstream>
#include <string.h>

GLMatrix4::GLMatrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33 )
{
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = m03;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = m13;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = m23;
    m[3][0] = m30;
    m[3][1] = m31;
    m[3][2] = m32;
    m[3][3] = m33;
}

GLMatrix4 GLMatrix4::multi(const GLMatrix4 &m2) const
{
    GLMatrix4 r;
    r.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0] + m[0][3] * m2.m[3][0];
    r.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1] + m[0][3] * m2.m[3][1];
    r.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2] + m[0][3] * m2.m[3][2];
    r.m[0][3] = m[0][0] * m2.m[0][3] + m[0][1] * m2.m[1][3] + m[0][2] * m2.m[2][3] + m[0][3] * m2.m[3][3];

    r.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0] + m[1][3] * m2.m[3][0];
    r.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1] + m[1][3] * m2.m[3][1];
    r.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2] + m[1][3] * m2.m[3][2];
    r.m[1][3] = m[1][0] * m2.m[0][3] + m[1][1] * m2.m[1][3] + m[1][2] * m2.m[2][3] + m[1][3] * m2.m[3][3];

    r.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0] + m[2][3] * m2.m[3][0];
    r.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1] + m[2][3] * m2.m[3][1];
    r.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2] + m[2][3] * m2.m[3][2];
    r.m[2][3] = m[2][0] * m2.m[0][3] + m[2][1] * m2.m[1][3] + m[2][2] * m2.m[2][3] + m[2][3] * m2.m[3][3];

    r.m[3][0] = m[3][0] * m2.m[0][0] + m[3][1] * m2.m[1][0] + m[3][2] * m2.m[2][0] + m[3][3] * m2.m[3][0];
    r.m[3][1] = m[3][0] * m2.m[0][1] + m[3][1] * m2.m[1][1] + m[3][2] * m2.m[2][1] + m[3][3] * m2.m[3][1];
    r.m[3][2] = m[3][0] * m2.m[0][2] + m[3][1] * m2.m[1][2] + m[3][2] * m2.m[2][2] + m[3][3] * m2.m[3][2];
    r.m[3][3] = m[3][0] * m2.m[0][3] + m[3][1] * m2.m[1][3] + m[3][2] * m2.m[2][3] + m[3][3] * m2.m[3][3];

    return r;
}

GLMatrix4::GLMatrix4(const GLMatrix4& matrix)
{
    for (int i=0; i<16; ++i)
        _m[i] = matrix._m[i];
}
void GLMatrix4::operator=(const GLMatrix4& matrix)
{
    for (int i=0; i<16; ++i)
        _m[i] = matrix._m[i];
}

void GLMatrix4::copy(float* dst) const
{
    memcpy(dst, _m, 16*sizeof(float));
}

void GLMatrix4::transform(float* out, float* in) const
{
    out[0] = m[0][0]* in[0] + m[0][1]* in[1] + m[0][2]* in[2] + m[0][3]* in[3];
    out[1] = m[1][0]* in[0] + m[1][1]* in[1] + m[1][2]* in[2] + m[1][3]* in[3];
    out[2] = m[2][0]* in[0] + m[2][1]* in[1] + m[2][2]* in[2] + m[2][3]* in[3];
    out[3] = m[3][0]* in[0] + m[3][1]* in[1] + m[3][2]* in[2] + m[3][3]* in[3];
}

std::string GLMatrix4::print()
{
    std::ostringstream os;
    os<<"\n";
    for (int i=0; i<4; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            os << m[i][j] <<" ";
        }
        os << "\n";
    }
    return os.str();
}
GLMatrix4 GLMatrix4::projection(float left, float right, float top, float bottom, float near, float far, float rate)
{
    GLMatrix4 result;
    for (int i=0; i<16; ++i) result._m[i] = 0;
    float A = 2 * near / (right - left);
    float B = 2 * near / (top - bottom);
    float C = (right + left) / (right - left);
    float D = (top + bottom) / (top - bottom);
    float q = -(far+near) / (far - near);
    float qn = -2 * (far * near) / (far - near);
    result.m[0][0] = A;
    result.m[0][2] = C;
    result.m[1][1] = B*rate;
    result.m[1][2] = D*rate;
    result.m[2][2] = q;
    result.m[2][3] = qn;
    result.m[3][2] = -1;
    return result;
}

GLMatrix4 GLMatrix4::ortho(float left, float right, float top, float bottom, float near, float far, float rate)
{
    GLMatrix4 result;
    for (int i=0; i<16; ++i) result._m[i] = 0;
    float A = 2.0 / (right - left);
    float B = 2.0 / (top - bottom);
    float C = - (right + left) / (right - left);
    float D = - (top + bottom) / (top - bottom);
    float q = -2.0 / (far - near);
    float qn = - (far + near) / (far - near);
    result.m[0][0] = A;
    result.m[0][3] = C;
    result.m[1][1] = B*rate;
    result.m[1][3] = D*rate;
    result.m[2][2] = q;
    result.m[2][3] = qn;
    result.m[3][3] = 1;
    return result;
}
