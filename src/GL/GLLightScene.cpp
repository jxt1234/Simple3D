#include "GL/GLLightScene.h"
#include <fstream>
#include <sstream>
#include "GL/GLSquareObjectCreator.h"
#include "utils/GLDebug.h"
#include "AllShader.h"

/*TODO Avoid use opengl directly*/
const std::string GLLightScene::gSceneName("LightScene");

GLLightScene::GLLightScene(int n)
{
    initDefaultAttr(mAttr);
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


bool GLLightScene::onGenerateShader(std::ostream& vertex, std::ostream& frag) const
{
    vertex<<glsl_light_vex;
    frag<<glsl_light_fra;
    return true;
}

void GLLightScene::vAddObject(GPPtr<GLObject> obj)
{
    bool res = obj->onPrepare();
    GLASSERT(true == res);
    if (res)
    {
        int programid = obj->vGetProgramId();
        if (0 == programid)
        {
            programid = mProgram->id();
        }
        GPPtr<GLObject> lobj = new GLLightObject(programid, mAttr, obj);
        mObjs.push_back(lobj);
    }
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
    mProgram = new GLProgram;
    std::ostringstream vex, fra;
    this->onGenerateShader(vex, fra);
    mProgram->load(vex.str().c_str(), fra.str().c_str());
    return mProgram->init();
}


GLObject* GLLightScene::vCreate(std::istream* parameter) const
{
    assert(NULL!=parameter);
    //TODO Expand
    GLTexture* t;
    parameter->read((char*)(&t), sizeof(t));
    GLSquareObjectCreator::SquarePara para;
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


GLLightScene::GLLightObject::GLLightObject(int proId, const GLLightAttr& attr, GPPtr<GLObject> basic):mProId(proId), mAttr(attr), mBasic(basic)
{
    OPENGL_CHECK_ERROR;
    mValid = true;
#define GET(x) mAttrId.x = glGetUniformLocation(proId, #x)
    GET(M);
    GET(V);
    GET(P);
    GET(N);
    GET(lightColor);
    GET(ambientColor);
    GET(lightpos);
    GET(eyepos);
    GET(ka);
    GET(kd);
    GET(ks);
    GET(ns);
#undef GET
    if (OPENGL_HAS_ERROR)
    {
        mValid = false;
        GLASSERT(mValid);
    }
}

GLLightScene::GLLightObject::~GLLightObject()
{
}
void GLLightScene::GLLightObject::onDraw(const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P)
{
    GLAutoDrawObject _o(mBasic, M, V, P);
    GLASSERT(mValid);
    if (!mValid)
    {
        return;
    }
    glUseProgram(mProId);
    OPENGL_CHECK_ERROR;
    GLMatrix4 N = M;
    N = N.transpose().inverse();
    GLProgram::setMatrix(M, mAttrId.M);
    GLProgram::setMatrix(V, mAttrId.V);
    GLProgram::setMatrix(P, mAttrId.P);
    GLProgram::setMatrix(N, mAttrId.N);
    glUniform4fv(mAttrId.lightColor, 1, mAttr.lightColor);
    OPENGL_CHECK_ERROR;
    glUniform4fv(mAttrId.ambientColor, 1, mAttr.ambientColor);
    OPENGL_CHECK_ERROR;
    glUniform4fv(mAttrId.lightpos, 1, mAttr.lightpos);
    OPENGL_CHECK_ERROR;
    glUniform4fv(mAttrId.eyepos, 1, mAttr.eyepos);
    OPENGL_CHECK_ERROR;
    glUniform1f(mAttrId.ka, mAttr.ka);
    OPENGL_CHECK_ERROR;
    glUniform1f(mAttrId.kd, mAttr.kd);
    OPENGL_CHECK_ERROR;
    glUniform1f(mAttrId.ks, mAttr.ks);
    OPENGL_CHECK_ERROR;
    glUniform1f(mAttrId.ns, mAttr.ns);
    OPENGL_CHECK_ERROR;
}
