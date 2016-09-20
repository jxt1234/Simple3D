#include "GLBasic3DObject.h"
#include "utils/GLAutoStorage.h"
#include "AllShader.h"
#include <ostream>


GLBasic3DObject::GLBasic3DObject(const GLBasicMesh* mesh, const GLBmp* texture)
{
    mTexture = new GLTexture;
    mTexture->upload(texture->pixels(), texture->width(), texture->height());
    GLASSERT(NULL!=mesh);
    auto points = mesh->get();
    {
        int unit = 4;
        GLAUTOSTORAGE(vertex, GLfloat, unit*mesh->size());
        int cur = 0;
        for (int i=0; i<mesh->size(); ++i)
        {
            auto p = points[i];
            for (int j=0; j<unit; ++j)
            {
                vertex[cur++] = p.vertex[j];
            }
        }
        mVertexes = new GLvboBuffer(vertex, unit, mesh->size());
    }
    {
        int unit = 3;
        GLAUTOSTORAGE(vertex, GLfloat, unit*mesh->size());
        int cur = 0;
        for (int i=0; i<mesh->size(); ++i)
        {
            for (int j=0; j<unit; ++j)
            {
                vertex[cur++] = points[i].normal[j];
            }
        }
        mNormal = new GLvboBuffer(vertex, unit, mesh->size());
    }
    {
        int unit = 2;
        GLAUTOSTORAGE(vertex, GLfloat, unit*mesh->size());
        int cur = 0;
        for (int i=0; i<mesh->size(); ++i)
        {
            for (int j=0; j<unit; ++j)
            {
                vertex[cur++] = points[i].uv[j];
            }
        }
        mUV = new GLvboBuffer(vertex, unit, mesh->size());
    }
    mProgram = new GLProgram;
    mProgram->load(glsl_basic3D_vex, glsl_basic3D_fra);
}

GLBasic3DObject::~GLBasic3DObject()
{
}


bool GLBasic3DObject::onGenerateShader(std::ostream& vertex, std::ostream& frag) const
{
    vertex << glsl_basic3D_vex;
    frag  << glsl_basic3D_fra;
    return true;
}

bool GLBasic3DObject::onPrepare()
{
    return mProgram->init();
}

int GLBasic3DObject::vGetProgramId() const
{
    return mProgram->id();
}

void GLBasic3DObject::onDraw(const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P)
{
    mProgram->use();
    mVertexes->use(mProgram->attr("aPos"));
    //mNormal->use(mProgram->attr("aNormal"));
    mUV->use(mProgram->attr("aTex"));
    GLProgram::setMatrix(M, mProgram->uniform("M"));
    GLProgram::setMatrix(V, mProgram->uniform("V"));
    GLProgram::setMatrix(P, mProgram->uniform("P"));
    mTexture->use();
    mUV->draw();
}

