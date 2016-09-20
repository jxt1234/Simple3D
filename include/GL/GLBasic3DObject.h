#ifndef GL_GLBASIC3DOBJECT_H
#define GL_GLBASIC3DOBJECT_H
#include "GLObject.h"
#include "GLProgram.h"
#include "GLvboBuffer.h"
#include "asset/GLBasicMesh.h"
#include "core/GLBmp.h"
#include "GLTexture.h"

CONTEXT_CLASS class GLBasic3DObject : public GLObject
{
public:
    GLBasic3DObject(const GLBasicMesh* mesh, const GLBmp* texture);
    virtual ~GLBasic3DObject();
    
    virtual bool onGenerateShader(std::ostream& vertex, std::ostream& frag) const;
    virtual bool onPrepare();
    virtual int vGetProgramId() const;
    virtual void onDraw(const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P);
private:
    GPPtr<GLProgram> mProgram;
    GPPtr<GLvboBuffer> mVertexes;
    GPPtr<GLvboBuffer> mNormal;
    GPPtr<GLvboBuffer> mUV;
    GPPtr<GLTexture> mTexture;
};
#endif
