#include "GL/GLLightCurveObj.h"
#include "math/FormulaTree.h"
#include "AllShader.h"
#include <iostream>

GLLightCurveObj::GLLightCurveObj(const IFunctionDeter* deter):sDeter(deter)
{
}
GLLightCurveObj::~GLLightCurveObj()
{
}
void GLLightCurveObj::getNormalCurve(std::ostream& vertex, const std::string& xf, const std::string& yf, const std::string& zf) const
{
    GLASSERT(NULL!=sDeter);
    FormulaTree x(sDeter, xf);
    FormulaTree y(sDeter, yf);
    FormulaTree z(sDeter, zf);
    if (!x.isvalid() || !y.isvalid() || !z.isvalid())
    {
        GLASSERT(false);
        return;
    }
    GPPtr<FormulaTree> xu = x.detByName("u");
    GPPtr<FormulaTree> xv = x.detByName("v");
    GPPtr<FormulaTree> yu = y.detByName("u");
    GPPtr<FormulaTree> yv = y.detByName("v");
    GPPtr<FormulaTree> zu = z.detByName("u");
    GPPtr<FormulaTree> zv = z.detByName("v");
    
    vertex << "vec3 normal_curve_transform(vec2 tex)\n{\n";
    vertex << "float u, v;\n";
    vertex << "u = (tex.x + uf)* us; v = (tex.y +vf)* vs;\n";
    vertex << "vec3 DU, DV;\n";
    vertex << "DU.x = "; xu->expand(vertex); vertex<<";\n";
    vertex << "DU.y = "; yu->expand(vertex); vertex<<";\n";
    vertex << "DU.z = "; zu->expand(vertex); vertex<<";\n";
    vertex << "DV.x = "; xv->expand(vertex); vertex<<";\n";
    vertex << "DV.y = "; yv->expand(vertex); vertex<<";\n";
    vertex << "DV.z = "; zv->expand(vertex); vertex<<";\n";
    vertex << " return cross(DU, DV);\n";
    vertex << "}\n";
}
void GLLightCurveObj::vGetVertex(std::ostream& vertex, const std::string& xf, const std::string& yf, const std::string& zf) const
{
    getVertexCurve(vertex, xf, yf, zf);
    getNormalCurve(vertex, xf, yf, zf);

    vertex << glsl_curve_light_vex;
}
void GLLightCurveObj::vGetFramgent(std::ostream& frag, const std::string& x, const std::string& y, const std::string& z) const
{
    frag << glsl_light_fra;
}
