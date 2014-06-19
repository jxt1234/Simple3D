#ifndef MATH_GLMATRIX4_H
#define MATH_GLMATRIX4_H
#include <assert.h>
#include <string>

class GLMatrix4
{
    public:
        GLMatrix4(){setUnit();}
        GLMatrix4(const GLMatrix4& matrix);
        void operator=(const GLMatrix4& matrix);
        GLMatrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33 );
        std::string print();
        void setUnit();
        void copy(float* dst) const;
        inline float* operator [](int iRow)
        {
            assert( iRow < 4 );
            return m[iRow];
        }
        inline const float *operator [](int iRow) const
        {
            assert( iRow < 4 );
            return m[iRow];
        }

        GLMatrix4 multi(const GLMatrix4 &m2) const;
        inline GLMatrix4 operator * ( const GLMatrix4 &m2 ) const { return multi(m2);}

        /*Assume the size of vector is 4*/
        void transform(float* out, float* in) const;

        static GLMatrix4 projection(float left, float right, float top, float bottom, float near, float far, float rate = 1.0);
        static GLMatrix4 ortho(float left, float right, float top, float bottom, float near, float far, float rate=1.0);
    protected:
        union{
            float m[4][4];
            float _m[16];
        };
};


#endif
