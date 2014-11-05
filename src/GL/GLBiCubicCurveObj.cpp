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

bool GLBiCubicCurveObj::onPrepare()
{
    bool res = INHERIT::onPrepare();
    //mTex->setFilter(false);
    return res;
}
void GLBiCubicCurveObj::vGetFramgent(std::ostream& frag, const std::string& x, const std::string& y, const std::string& z) const
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
