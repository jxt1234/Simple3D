#include "GL/GLLightScene.h"
#include <fstream>
#include <sstream>

GLLightScene::GLLightScene(int n)
{
    mProgram = new GLProgram;
    initDefaultAttr(mAttr);
    std::ostringstream vex, fra;
    this->onGenerateShader(vex, fra);
    mProgram->load(vex.str().c_str(), fra.str().c_str());
}
GLLightScene::~GLLightScene()
{
}

void GLLightScene::initDefaultAttr(GLLightAttr& attr)
{
    GLVector::setVec4(100,100,100,1, attr.lightpos);
    GLVector::setVec4(1.0,1.0,1.0,1.0, attr.lightColor);
    GLVector::setVec4(-100,100,100,1, attr.eyepos);
    GLVector::setVec4(1.0,1.0,1.0,1.0, attr.ambientColor);
    attr.ka = 0.0;
    attr.kd = 1.0;
    attr.ks = 1.0;
    attr.ns = 0.5;
}
void GLLightScene::setEyePos(float x, float y, float z)
{
    GLVector::setVec4(x, y, z, 1.0, mAttr.eyepos);
}

void GLLightScene::setLightNumber(int n)
{
    //TODO
}

void GLLightScene::setLightPos(int n, float x, float y, float z)
{
    //TODO Support multi light
    GLVector::setVec4(x, y, z, 1.0, mAttr.lightpos);
}


void GLLightScene::onGenerateShader(std::ostream& vertex, std::ostream& frag) const
{
    /*FIXME For debug*/
    std::ifstream vexf("light.vex");
    vertex<<vexf.rdbuf();
    vexf.close();
    std::ifstream fragf("light.fra");
    frag<<fragf.rdbuf();
    fragf.close();
}

void GLLightScene::vAddObject(GPPtr<GLObject> obj)
{
    mObjs.push_back(obj);
}

void GLLightScene::vRemoveAll()
{
    mObjs.clear();
}

void GLLightScene::vRemoveObject(GPPtr<GLObject> obj)
{
    std::vector<GPPtr<GLObject> >::iterator iter;
    for (iter=mObjs.begin(); iter!=mObjs.end(); iter++)
    {
        GLObject* _obj = (*iter).get();
        if (_obj == obj.get())
        {
            iter = mObjs.erase(iter);
            break;
        }
    }
}

void GLLightScene::onPrepare()
{
    mProgram->use();
}


GLObject* GLLightScene::vCreate(std::istream* parameter) const
{
    GPPtr<GLLightObject> basic = new GLLightObject(*mProgram, mAttr);
    return basic.get();
}

void GLLightScene::vGetInfo(std::ostream& output) const
{
}


GLLightScene::GLLightObject::GLLightObject(const GLProgram& pro, const GLLightAttr& attr):mProgram(pro), mAttr(attr)
{
}

GLLightScene::GLLightObject::~GLLightObject()
{
}
/*TODO Optimize this*/
void GLLightScene::GLLightObject::onDraw(const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P)
{
    int id = mProgram.id();
    GLProgram::setMatrix(M, mProgram.uniform("M"));
    GLProgram::setMatrix(V, mProgram.uniform("V"));
    GLProgram::setMatrix(P, mProgram.uniform("P"));
    /*TODO Avoid use opengl directly*/
    glUniform4fv(mProgram.uniform("lightColor"), 1, mAttr.lightColor);
    OPENGL_CHECK_ERROR;
    glUniform4fv(mProgram.uniform("ambientColor"), 1, mAttr.ambientColor);
    OPENGL_CHECK_ERROR;
    glUniform4fv(mProgram.uniform("lightpos"), 1, mAttr.lightpos);
    OPENGL_CHECK_ERROR;
    glUniform4fv(mProgram.uniform("eyepos"), 1, mAttr.eyepos);
    OPENGL_CHECK_ERROR;
    glUniform1f(mProgram.uniform("ka"), mAttr.ka);
    OPENGL_CHECK_ERROR;
    glUniform1f(mProgram.uniform("kd"), mAttr.kd);
    OPENGL_CHECK_ERROR;
    glUniform1f(mProgram.uniform("ks"), mAttr.ks);
    OPENGL_CHECK_ERROR;
    glUniform1f(mProgram.uniform("ns"), mAttr.ns);
    OPENGL_CHECK_ERROR;
}
