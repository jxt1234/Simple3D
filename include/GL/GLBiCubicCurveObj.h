#ifndef GL_GLBICUBICCURVEOBJ_H
#define GL_GLBICUBICCURVEOBJ_H
#include "GLCurveObject.h"
#include "GL/GLBitmapWork.h"
class GLBiCubicCurveObj:public GLCurveObject
{
    public:
        GLBiCubicCurveObj();
        virtual ~GLBiCubicCurveObj();
        virtual void onDraw(const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P);
        virtual bool onPrepare();
    private:
        virtual void vGetFramgent(std::ostream& frag) const;

        GPPtr<GLBitmapWork> mWork;
        typedef GLCurveObject INHERIT;
};
#endif
