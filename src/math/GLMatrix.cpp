#include "math/GLMatrix4.h"
#include <sstream>
#include <string.h>
#include <math.h>
void GLMatrix4::reset()
{
    for (int i=0; i<16; ++i)
    {
        _m[i] = 0;
    }
    for (int i=0; i<4; ++i)
    {
        m[i][i] = 1;
    }
}
/*Copy from Ogre*/
GLMatrix4 GLMatrix4::inverse() const
{
    float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
    float m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
    float m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
    float m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

    float v0 = m20 * m31 - m21 * m30;
    float v1 = m20 * m32 - m22 * m30;
    float v2 = m20 * m33 - m23 * m30;
    float v3 = m21 * m32 - m22 * m31;
    float v4 = m21 * m33 - m23 * m31;
    float v5 = m22 * m33 - m23 * m32;

    float t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
    float t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
    float t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
    float t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

    float invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

    float d00 = t00 * invDet;
    float d10 = t10 * invDet;
    float d20 = t20 * invDet;
    float d30 = t30 * invDet;

    float d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
    float d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
    float d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
    float d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

    v0 = m10 * m31 - m11 * m30;
    v1 = m10 * m32 - m12 * m30;
    v2 = m10 * m33 - m13 * m30;
    v3 = m11 * m32 - m12 * m31;
    v4 = m11 * m33 - m13 * m31;
    v5 = m12 * m33 - m13 * m32;

    float d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
    float d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
    float d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
    float d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

    v0 = m21 * m10 - m20 * m11;
    v1 = m22 * m10 - m20 * m12;
    v2 = m23 * m10 - m20 * m13;
    v3 = m22 * m11 - m21 * m12;
    v4 = m23 * m11 - m21 * m13;
    v5 = m23 * m12 - m22 * m13;

    float d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
    float d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
    float d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
    float d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

    return GLMatrix4(
            d00, d01, d02, d03,
            d10, d11, d12, d13,
            d20, d21, d22, d23,
            d30, d31, d32, d33);
}

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
void GLMatrix4::setRotate(float x, float y, float z, float rad)
{
    reset();
    float r = sqrt(x*x+y*y+z*z);
    float nx = x/r;
    float ny = y/r;
    float nz = z/r;
    float cr = cos(rad);
    float sr = sin(rad);
    m[0][0] = nx*nx*(1-cr) + cr;
    m[1][0] = nx*ny*(1-cr) + nz*sr;
    m[2][0] = nx*nz*(1-cr) - ny*sr;
    m[0][1] = nx*ny*(1-cr) - nz*sr;
    m[1][1] = ny*ny*(1-cr) + cr;
    m[2][1] = ny*nz*(1-cr) + nx*sr;
    m[0][2] = nx*nz*(1-cr) + ny*sr;
    m[1][2] = ny*nz*(1-cr) - nx*sr;
    m[2][2] = nz*nz*(1-cr) + cr;
}
void GLMatrix4::setScale(float x, float y, float z)
{
    reset();
    m[0][0] = x;
    m[1][1] = y;
    m[2][2] = z;
}
void GLMatrix4::setTranslate(float x, float y, float z)
{
    reset();
    m[0][3] = x;
    m[1][3] = y;
    m[2][3] = z;
}
