#include "GL/GLLightScene.h"
#include <fstream>
#include <sstream>
#include "GL/GLSquareObjectCreator.h"
#include "utils/debug.h"

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
    attr.ns = 11.0;
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

bool GLLightScene::onPrepare()
{
    return mProgram->init();
}


GLObject* GLLightScene::vCreate(std::istream* parameter) const
{
    assert(NULL!=parameter);
    //TODO Expand
    GLTexture* t;
    parameter->read((char*)(&t), sizeof(t));
    GPPtr<GLLightObject> basic = new GLLightObject(*mProgram, mAttr);
    GLSquareObjectCreator::SquarePara para;
    para.basic = basic.get();
    para.t = t;
    mProgram->use();
    para.verId = mProgram->attr("aPos");
    para.normaliId = mProgram->attr("aNormal");
    para.texId = mProgram->attr("aTex");
    std::ostringstream os;
    os.write((char*)(&para), sizeof(para));
    std::istringstream is(os.str());
    GLSquareObjectCreator c;
    GLObject* obj = c.vCreate(&is);
    return obj;
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
    GLMatrix4 N = M;
    N = N.transpose().inverse();
    GLProgram::setMatrix(M, mProgram.uniform("M"));
    GLProgram::setMatrix(V, mProgram.uniform("V"));
    GLProgram::setMatrix(P, mProgram.uniform("P"));
    GLProgram::setMatrix(N, mProgram.uniform("N"));
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
