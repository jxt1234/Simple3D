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
void GLBiCubicCurveObj::vGetFramgent(std::ostream& frag) const
{
    std::ostringstream vert;//Not use
    mWork->GetShader(vert, frag);
}
void GLBiCubicCurveObj::onDraw(const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P)
{
    program().useSingle();
    mWork->use(program().id(), texture()->width(), texture()->height());
    GLCurveObject::onDraw(M,V,P);
}
