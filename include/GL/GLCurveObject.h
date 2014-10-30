#ifndef GL_GLCURVEOBJECT_H
#define GL_GLCURVEOBJECT_H
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
        void setColor(uint32_t color);
        void setVBO(GLvboBuffer* vbo);
        inline void setScale(float us, float vs){mUs = us, mVs = vs;}
        inline void setOffset(float uf, float vf) {mUf = uf, mVf = vf;}
        virtual void onDraw(const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P);
        virtual bool onPrepare();
    protected:
        GLProgram mPro;
        GLTexture* mTex;
    private:
        virtual void vGetVertex(std::ostream& vertex, const std::string& xf, const std::string& yf, const std::string& zf) const;
        virtual void vGetFramgent(std::ostream& frag) const;
        GLvboBuffer* mVbo;
        /*u = mUs*(u+mUf), y = mVs*(v+mVf)*/
        float mUs;
        float mVs;
        float mUf;
        float mVf;

        uint32_t mColor;
};
#endif
