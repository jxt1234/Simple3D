#include "GL/GLLightScene.h"
const static std::string trans_m("transform");
const static std::string proj_m("projection");
const static std::string normal("normal");
const static std::string vertex("vertex");
const static std::string texcord("texcord");
const static std::string texture("texture");


GLLightScene::GLLightScene(int n)
{
    mProgram = new GLProgram;
}
GLLightScene::~GLLightScene()
{
}

void GLLightScene::setLightNumber(int n)
{
}

void GLLightScene::setLightPos(int n, GLVector::vec3 pos)
{
}


void GLLightScene::onGenerateShader(std::ostream& vertex, std::ostream& frag) const
{
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
    GPPtr<GLLightObject> basic = new GLLightObject(mProgram, mLights);
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
void GLLightScene::GLLightObject::onDraw(const GLMatrix4& transform, const GLMatrix4& projection)
{
    int id = mProgram.id();
}
