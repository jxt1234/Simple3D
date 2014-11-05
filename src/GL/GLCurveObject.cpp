#include "GL/GLCurveObject.h"
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
const static string trans_m("modle_m");
const static string view_m("view_m");
const static string proj_m("projection");
const static string us_f("us");
const static string vs_f("vs");
const static string uf_f("uf");
const static string vf_f("vf");
const static string tex_v("Tex");
const static string vTex("vTex");
const static string texture_s("texture");

const static bool DEBUG = false;

void GLCurveObject::getVertexCurve(std::ostream& vertex, const std::string& xf, const std::string& yf, const std::string& zf)
{
    vertex << "uniform float "<<us_f <<";\n";
    vertex << "uniform float "<<vs_f <<";\n";
    vertex << "uniform float "<<uf_f <<";\n";
    vertex << "uniform float "<<vf_f <<";\n";
    vertex << "vec4 curve_transform(vec2 tex){\n";
    vertex << "vec4 temp = vec4(1.0);\n";
    vertex << "float u,v;\n";
    vertex << "u = (tex.x + "+uf_f+ ")* "<<us_f<<"; v = (tex.y +"+vf_f +")* "<<vs_f<<";\n";
    vertex << "temp.x = " << xf << ";\n";
    vertex << "temp.y = " << yf << ";\n";
    vertex << "temp.z = " << zf << ";\n";
    vertex << "return temp;\n}\n";
}
void GLCurveObject::vGetVertex(std::ostream& vertex, const std::string& xf, const std::string& yf, const std::string& zf) const
{
    //Vertex shader
    getVertexCurve(vertex, xf, yf, zf);
    vertex << "attribute vec2 "<<tex_v<<";\n";
    vertex << "varying vec2 "<<vTex<<";\n";
    vertex << "uniform mat4 "<<trans_m <<";\n";
    vertex << "uniform mat4 "<<view_m <<";\n";
    vertex << "uniform mat4 "<<proj_m <<";\n";
    vertex << "void main(void)\n{\n";
    //Compute Curve
    vertex << "vec4 temp = curve_transform("<<tex_v<<");\n";
    //Compute MVP
    vertex << "temp = temp*"<<trans_m <<"*"<<view_m<<" * "<<proj_m<<";\n";
    vertex << "gl_Position = temp;\n";
    vertex << vTex <<" = "<<tex_v<<";\n";
    vertex << "}\n";
}

void GLCurveObject::vGetFramgent(std::ostream& frag, const std::string& x, const std::string& y, const std::string& z) const
{
    //Fragment shader
    frag << "precision mediump float;\n";
    frag << "uniform sampler2D "<<texture_s<<";\n";
    frag << "varying vec2 "<<vTex<<";\n";
    frag << "void main(void)\n{\n";
    frag << "gl_FragColor = texture2D("<<texture_s << ", "<<vTex<<");\n";
    frag << "}\n";
}

/*Vertex*/
/*x = x(t), y=y(t), z=z(t);
 GL_position = x,y,z,1 * transform* projection*/
/*Fragment: color = texture2D(u,v)*/
GLCurveObject::GLCurveObject()
{
    mTex = NULL;
    mVbo = NULL;
    mUs = 1.0;
    mVs = 1.0;
    mUf = 0.0;
    mVf = 0.0;
    mColor = 0xFF00FFFF;
}
GLCurveObject::~GLCurveObject()
{
    mPro.destroy();
    SAFE_UNREF(mTex);
    SAFE_UNREF(mVbo);
}
void GLCurveObject::setTexture(GLTexture* tex)
{
    GLASSERT(NULL!=tex);
    tex->addRef();
    SAFE_UNREF(mTex);
    mTex = tex;
}
void GLCurveObject::setVBO(GLvboBuffer* vbo)
{
    GLASSERT(NULL!=vbo);
    vbo->addRef();
    SAFE_UNREF(mVbo);
    mVbo = vbo;
}

void GLCurveObject::setFormula(const std::string& formula_x, const std::string& formula_y, const std::string& formula_z)
{
    ostringstream vertex, frag;
    this->vGetVertex(vertex, formula_x, formula_y, formula_z);
    if (DEBUG)
    {
        ofstream os("curve.vex");
        this->vGetVertex(os, formula_x, formula_y, formula_z);
    }
    this->vGetFramgent(frag, formula_x, formula_y, formula_z);
    if (DEBUG)
    {
        ofstream os("curve.fra");
        this->vGetFramgent(os, formula_x, formula_y, formula_z);
    }
    mPro.load(vertex.str(), frag.str());
}
void GLCurveObject::setColor(uint32_t argb)
{
    mColor = argb;
}
bool GLCurveObject::onPrepare()
{
    if (NULL == mTex)
    {
        mTex = new GLTexture();
        mTex->upload(&mColor, 1, 1);
    }
    bool res = mPro.init();
    mTex->setFilter(true);
    return res;
}
void GLCurveObject::onDraw(const GLMatrix4& transform, const GLMatrix4& view, const GLMatrix4& projection)
{
    GLASSERT(NULL!=mVbo);
    if (!mPro.init()) return;
    mPro.use();
    mTex->use();
    GLProgram::setMatrix(projection, mPro.uniform(proj_m.c_str()));
    GLProgram::setMatrix(transform, mPro.uniform(trans_m.c_str()));
    GLProgram::setMatrix(view, mPro.uniform(view_m.c_str()));
    GLProgram::setUniform(mUs, mPro.uniform(us_f.c_str()));
    GLProgram::setUniform(mVs, mPro.uniform(vs_f.c_str()));
    GLProgram::setUniform(mUf, mPro.uniform(uf_f.c_str()));
    GLProgram::setUniform(mVf, mPro.uniform(vf_f.c_str()));
    mVbo->use(mPro.attr(tex_v.c_str()));
    mVbo->draw();
}
