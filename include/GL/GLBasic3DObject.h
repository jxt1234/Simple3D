#ifndef GL_GLBASIC3DOBJECT_H
#define GL_GLBASIC3DOBJECT_H
#include "GLObject.h"
#include "GLProgram.h"
#include "GLvboBuffer.h"
#include "asset/GLBasicMesh.h"
#include "core/GLBmp.h"
#include "GLTexture.h"
#include "3d/CCBundle3D.h"
#include <vector>

CONTEXT_CLASS class GLBasic3DObject : public GLObject
{
public:
    class Node : public GPRefCount
    {
    public:
        Node(const NodeData* node, const MeshDatas& mesh, const MaterialDatas& material, const std::map<std::string, GPPtr<GLTexture>>& textures);
        virtual ~ Node();
        
        void draw(const GLProgram* program, const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P);
        
    private:
        std::vector<GPPtr<Node>> mChildren;
        GLMatrix4 mTransform;
        GPPtr<GLvboBuffer> mVertexes;
        GPPtr<GLvboBuffer> mNormal;
        GPPtr<GLvboBuffer> mUV;
        GPPtr<GLTexture> mTexture;
    };
    
    GLBasic3DObject(const NodeDatas& node, const MeshDatas& mesh, const MaterialDatas& material);
    virtual ~GLBasic3DObject();
    
    virtual bool onGenerateShader(std::ostream& vertex, std::ostream& frag) const;
    virtual bool onPrepare();
    virtual int vGetProgramId() const;
    virtual void onDraw(const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P);
private:
    GPPtr<GLProgram> mProgram;
    GPPtr<Node> mRoot;
};
#endif
