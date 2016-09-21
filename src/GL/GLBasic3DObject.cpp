#include "GL/GLBasic3DObject.h"
#include "utils/GLAutoStorage.h"
#include "AllShader.h"
#include <ostream>
#include <sstream>


GLBasic3DObject::GLBasic3DObject(const NodeDatas& node, const MeshDatas& mesh, const MaterialDatas& material)
{
    std::map<std::string, GPPtr<GLTexture>> textureMaps;
    for (auto m : material.materials)
    {
        if (m.textures.empty())
        {
            continue;
        }
        FUNC_PRINT(m.textures.size());
        auto &t = m.textures[0];
        std::ostringstream fullPath;
        fullPath << "/Users/jiangxiaotang/fbx/tank.fbm/"<<t.filename;
        
        GPPtr<GLTexture> texture = new GLTexture;
        GPPtr<GLBmp> bmp = new GLBmp(fullPath.str().c_str());
        texture->upload(bmp->pixels(), bmp->width(), bmp->height());
        textureMaps.insert(std::make_pair(m.id, texture));
    }
    
    mRoot = new Node(node.nodes[0], mesh, material, textureMaps);
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
    mRoot->draw(mProgram.get(), M, V, P);
}

GLBasic3DObject::Node::Node(const NodeData* node, const MeshDatas& meshs, const MaterialDatas& material, const std::map<std::string, GPPtr<GLTexture>>& textures)
{
    for (auto c : node->children)
    {
        mChildren.push_back(new Node(c, meshs, material, textures));
    }
    mTransform = node->transform;
    if (node->modelNodeDatas.empty())
    {
        return;
    }
    //FUNC_PRINT(node->modelNodeDatas.size());
    auto modelData = node->modelNodeDatas[0];
    std::vector<unsigned short>* index = NULL;
    MeshData* origin = NULL;
    for (auto m : meshs.meshDatas)
    {
        bool find = false;
        for (int i=0; i<m->subMeshIndices.size(); ++i)
        {
            if (m->subMeshIds[i] == modelData->subMeshId)
            {
                find = true;
                index = &m->subMeshIndices[i];
                origin = m;
                break;
            }
        }
        if (find)
        {
            break;
        }
    }
    GLASSERT(NULL!=origin && NULL!=index);
    GLAUTOSTORAGE(vertex, float, (*index).size()*3);
    GLAUTOSTORAGE(uv, float, (*index).size()*3);
    auto perVertexSize = origin->getPerVertexSize()/sizeof(float);
    for (int i=0; i<index->size(); ++i)
    {
        auto dstPos = 3*i;
        auto srcPos = perVertexSize*(*index)[i];
        for (int j=0; j<3; ++j)
        {
            vertex[dstPos+j] = origin->vertex[srcPos+j];
        }
        uv[2*i] = origin->vertex[srcPos+6];
        uv[2*i+1] = origin->vertex[srcPos+7];
    }
    mVertexes = new GLvboBuffer(vertex, 3, (int)index->size());
    mUV = new GLvboBuffer(uv, 2, (int)index->size());
    
    //FUNC_PRINT_ALL(modelData->matrialId.c_str(), s);
    auto matrialId = modelData->matrialId;
    if ("" == matrialId)
    {
        matrialId = material.materials[0].id;
    }
    auto textureIter = textures.find(modelData->matrialId);
    if (textureIter!=textures.end())
    {
        mTexture = textureIter->second;
    }
}
GLBasic3DObject::Node::~Node()
{
}

void GLBasic3DObject::Node::draw(const GLProgram* program, const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P)
{
    //auto subM = mTransform*M;
    auto subM = M;
    if (NULL != mTexture.get())
    {
        mVertexes->use(program->attr("aPos"));
        //mNormal->use(mProgram->attr("aNormal"));
        mUV->use(program->attr("aTex"));
        GLProgram::setMatrix(subM, program->uniform("M"));
        GLProgram::setMatrix(V, program->uniform("V"));
        GLProgram::setMatrix(P, program->uniform("P"));
        mTexture->use();
        mUV->draw();
    }
    for (auto c : mChildren)
    {
        c->draw(program, subM, V, P);
    }
}

