#ifndef MATH_GLMATRIX4_H
#define MATH_GLMATRIX4_H
#include <assert.h>
#include <string>

class GLMatrix4
{
    public:
        GLMatrix4(){reset();}
        GLMatrix4(const GLMatrix4& matrix);
        void operator=(const GLMatrix4& matrix);
        GLMatrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33 );
        std::string print();
        void reset();
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

        GLMatrix4 inverse() const;
        GLMatrix4 multi(const GLMatrix4 &m2) const;
        inline GLMatrix4 operator * ( const GLMatrix4 &m2 ) const { return multi(m2);}
        inline GLMatrix4 transpose(void) const
        {
            return GLMatrix4(m[0][0], m[1][0], m[2][0], m[3][0],
                           m[0][1], m[1][1], m[2][1], m[3][1],
                           m[0][2], m[1][2], m[2][2], m[3][2],
                           m[0][3], m[1][3], m[2][3], m[3][3]);
        }
        /*Transform*/
        void setRotate(float x, float y, float z, float radium);
        void setScale(float x, float y, float z);
        void setTranslate(float x, float y, float z);

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
