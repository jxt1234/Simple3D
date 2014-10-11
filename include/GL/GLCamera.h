#ifndef GL_GLCAMERA_H
#define GL_GLCAMERA_H
#include "math/GLMatrix4.h"
#include "math/GLVector.h"
class GLCamera
{
    public:
        inline const GLMatrix4& get() const {return mProjection;}
        GLCamera(int w, int h);
        ~GLCamera();
        inline void setPoint(GLVector::vec3 pos) {mPos[0] = pos[0], mPos[1] = pos[1], mPos[2]=pos[2];}
        //The Plane is set to be perpendicular to the line from project point to zero point
        inline void setPlane(float near, float seta){mNear = near, mSeta = seta;}
        void transform(const GLMatrix4& trans);
        inline int width() const {return mWidth;}
        inline int height() const {return mHeight;}
        void invalidate();
    private:
        GLMatrix4 mProjection;
        /*The viewport's w and h is attached to this camera, becase camera will use them to adjust projection matrix*/
        int mWidth;
        int mHeight;
        GLVector::vec3 mPos;
        float mNear;
        float mSeta;
};
#endif
