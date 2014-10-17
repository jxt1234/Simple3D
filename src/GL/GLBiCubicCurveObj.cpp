#include "GL/GLBiCubicCurveObj.h"
#include "GL/GLBitmapWorkFactory.h"
#include <sstream>

GLBiCubicCurveObj::GLBiCubicCurveObj()
{
    mWork = GLBitmapWorkFactory::create("Bicubic");
}
GLBiCubicCurveObj::~GLBiCubicCurveObj()
{
    mWork = NULL;
}

void GLBiCubicCurveObj::onPrepare()
{
    INHERIT::onPrepare();
    //mTex->setFilter(false);
}
void GLBiCubicCurveObj::vGetFramgent(std::ostream& frag) const
{
    std::ostringstream vert;//Not use
    mWork->work()->onGenerateShader(vert, frag);
}
void GLBiCubicCurveObj::onDraw(const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P)
{
    mPro.use();
    std::vector<GLTexture*> _s(1, mTex);
    mWork->work()->onUse(NULL, _s, &mPro);
    INHERIT::onDraw(M,V,P);
}
