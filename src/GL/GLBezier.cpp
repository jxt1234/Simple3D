#include "GL/GLBezier.h"
#include "utils/debug.h"
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
//#define DEBUG

GLBezier::GLBezier(int precision, float width)
{
    mWidth = width;
    mControl = new GL_position;
    mParameter = NULL;
    mColor[0] = 1.0;
    mColor[1] = 1.0;
    mColor[2] = 0.0;
    mColor[3] = 1.0;
    float* p = new float[precision+1];
    float step= 1.0/precision;
    for (int i=0; i<=precision; ++i)
    {
        p[i] = step*i;
    }
    mVertex = new GLvboBuffer(p, 1, precision+1);
    delete [] p;
}

GLBezier::~GLBezier()
{
    if (NULL != mParameter)
    {
        delete [] mParameter;
        mParameter = NULL;
    }
    delete mControl;
    mVertex->decRef();
    mProgram.destroy();
}

void GLBezier::clean()
{
    delete mControl;
    mControl = new GL_position;
    _sync();
}

void GLBezier::_sync()
{
    if (NULL != mParameter)
    {
        delete [] mParameter;
        mParameter = NULL;
    }
    int n = mControl->size()-1;
    if (n>0)
    {
        mParameter = new float[n+1];
        /*mParameter[i] = C(n, i)*/
        mParameter[0] = 1;
        for (int i=0; i<n; ++i)
        {
            mParameter[i+1] = mParameter[i]*(n-i)/(i+1);
        }
    }
#ifdef DEBUG
    FUNC_PRINT(n);
    for (int i=0; i<=n; ++i)
    {
        FUNC_PRINT_ALL(mParameter[i], f);
    }
#endif
}

const static string U("u");
const static string VEX("p");
const static string COLOR("color");
const static string trans_m("transform");
const static string proj_m("projection");

void GLBezier::_genShader(ostream& vertex, ostream& frag)
{
    vertex << "attribute float "<<U<<";\n";
    //TODO Add Project
    vertex << "uniform mat4 "<<trans_m <<";\n";
    vertex << "uniform mat4 "<<proj_m <<";\n";
    for (int i=0; i<mControl->size(); ++i)
    {
        vertex << "uniform vec4 "<<VEX<<i<<";\n";
    }
    vertex << "void main(void)\n{\n";
    vertex << "vec4 temp = vec4(0.0)\n";
    int n = mControl->size() - 1;
    for (int i=0; i<mControl->size(); ++i)
    {
        vertex << "+"<<VEX<<i<<"*float("<<mParameter[i] << ")*"<<"pow("<<U<<", float("<<i<<"))*pow((1.0-"<<U<<"),float("<<n-i<<"))\n";
    }
    vertex << ";\n";

    vertex << "gl_Position = "<<trans_m <<" * "<<proj_m<<" * temp;\n";
    //vertex << "gl_Position = temp;\n";//For debug

    vertex<<"}\n";

    frag << "uniform vec4 "<<COLOR<<";\n";
    frag << "void main(void)\n{\n";
    frag << "gl_FragColor = "<<COLOR<<";\n";
    frag << "}\n";
}
void GLBezier::onPrepare()
{
    _sync();
#ifdef DEBUG
    ofstream ver("vertex.vex");
    ofstream fra("frage.fra");
    _genShader(ver, fra);
    ver.close();
    fra.close();
#endif
    ostringstream vertex, frag;
    _genShader(vertex, frag);

    mProgram.load(vertex.str(), frag.str());
}

void GLBezier::addPoint(float x, float y, float z)
{
    mControl->addPoint(x, y, z, 1.0);
}

void GLBezier::setColor(float a, float r, float g, float b)
{
    mColor[0] = a;
    mColor[1] = r;
    mColor[2] = g;
    mColor[3] = b;
}

void GLBezier::reset(int precision)
{
    mVertex->decRef();
    float* p = new float[precision+1];
    float step= 1.0/precision;
    for (int i=0; i<=precision; ++i)
    {
        p[i] = step*i;
    }
    mVertex = new GLvboBuffer(p, 1, precision+1);
    delete [] p;
}
void GLBezier::onDraw(const GLMatrix4& transform, const GLMatrix4& projection)
{
    mProgram.use();
    for (int i=0; i<mControl->size(); ++i)
    {
        ostringstream os;
        os << VEX<<i;
        glUniform4fv(mProgram.uniform(os.str().c_str()), 1, mControl->load(i));//FIXME
    }
    glUniform4fv(mProgram.uniform(COLOR.c_str()), 1, mColor);//FIXME
    GLProgram::setMatrix(transform, mProgram.uniform(trans_m.c_str()));
    GLProgram::setMatrix(projection, mProgram.uniform(proj_m.c_str()));

    glLineWidth(mWidth);//FIXME avoid use opengl directly
    mVertex->use(mProgram.attr(U.c_str()));
    mVertex->setType(GL_LINE);
    mVertex->draw();
}
