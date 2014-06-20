#ifndef MATH_GLCURVESURFACE_H
#define MATH_GLCURVESURFACE_H

/*Abstract Curve Surface*/

struct GLRectArea
{
    float x1;
    float x2;
    float y1;
    float y2;

    float ux;
    float uy;
    void set(float _x1, float _y1, float _x2, float _y2, float _ux, float _uy)
    {
        x1 = _x1;
        x2 = _x2;
        y1 = _y1;
        y2 = _y2;
        ux = _ux;
        uy = _uy;
    }
};


class GLCurveSurface
{
    public:
        GLCurveSurface(){}
        virtual ~GLCurveSurface(){}
        virtual void pos(float* out, float u, float v) = 0;
        virtual void normal(float* out, float u, float v) = 0;
};

class GLEmptyCurveSurface:public GLCurveSurface
{
    public:
        GLEmptyCurveSurface(){}
        ~GLEmptyCurveSurface(){}
        virtual void pos(float* out, float u, float v){}
        virtual void normal(float* out, float u, float v){}
};


#endif
