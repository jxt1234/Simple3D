#ifndef DISPLAY_GLCURVEOBJECT_H
#define DISPLAY_GLCURVEOBJECT_H
#include "GLObject.h"
#include <string>
#include <vector>
#include "GLProgram.h"
#include "GLTexture.h"
#include "GLvboBuffer.h"
/*Curve:
 x = xf(u*us, v*vs)
 y = yf(u*us, v*vs)
 z = zf(u*us, v*vs)

 color = texture2D(u,v)
 */
class GLCurveObject:public GLObject
{
    public:
        GLCurveObject();
        virtual ~GLCurveObject();
        CONTEXT_FREE_API void setFormula(const std::string& formula_x, const std::string& formula_y, const std::string& formula_z);
        void setTexture(GLTexture* tex);
        void setColor(unsigned int argb);
        void setVBO(GLvboBuffer* vbo);
        inline void setScale(float us, float vs){mUs = us, mVs = vs;}
        inline void setOffset(float uf, float vf) {mUf = uf, mVf = vf;}
        virtual void onDraw(const GLMatrix4& transform, const GLMatrix4& projection);
        static void GenerateShader(std::ostream& vertex, std::ostream& frag, const std::string& xf, const std::string& yf, const std::string& zf);
    private:
        GLProgram mPro;
        GLTexture* mTex;
        GLvboBuffer* mVbo;
        /*u = mUs*(u+mUf), y = mVs*(v+mVf)*/
        float mUs;
        float mVs;
        float mUf;
        float mVf;
};
#endif
