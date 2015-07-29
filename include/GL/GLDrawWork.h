#ifndef GL_GLDRAWWORK_H
#define GL_GLDRAWWORK_H
#include "head.h"
#include "core/GLBmp.h"
#include "GL/GLTexture.h"
#include "GL/GLProgram.h"
#include "GL/GLvboBuffer.h"
#include "GL/IGLDrawWork.h"
#include <string>
#include <vector>
#include <map>
/*DrawWork For Single Work*/
class GLDrawWork:public IGLDrawWork
{
public:
    /*If vertex/frag is NULL, use default shader*/
    GLDrawWork(const std::string& vertex, const std::string& frag, const std::map<std::string, float>* uniforms, const std::vector<GLBmp*>* resources = NULL, int inputnumber=1);
    virtual ~GLDrawWork();
    virtual void onDraw(GLTexture** src, int number, GLvboBuffer* vs, GLvboBuffer* ts);

    /*All parameters is in [0,1), set self parameters by these, if parameters is NULL, don't do anything just return the number of parameters needed*/
    virtual size_t vMap(double* parameters, size_t n);
    void setUniform(const std::string& name, float value);
    
    
private:
    virtual void onSetupVertex();
    virtual void onSetupFragment();
    std::vector<GPPtr<GLTexture> > mResources;
    std::vector<int> mResoucePos;
    std::vector<int> mInputPos;
    GPPtr<GLProgram> mProgram;
    std::map<int, float> mUniforms;
    std::map<std::string, int> mUniformOrder;
    int mTextureCorderPos;
    int mVertexPos;
};
#endif
