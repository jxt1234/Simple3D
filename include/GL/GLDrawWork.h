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
    GLDrawWork(const std::string& vertex, const std::string& frag, const std::map<std::string, float>* uniforms = NULL, const std::vector<GLBmp*>* resources = NULL);
    virtual ~GLDrawWork();
    virtual void onDraw(GLTexture* src, GLvboBuffer* vs, GLvboBuffer* ts);

    /*All parameters is in [0,1), set self parameters by these, if parameters is NULL, don't do anything just return the number of parameters needed*/
    virtual int vMap(double* parameters, int n);
    
protected:
    virtual void onSetupVertex();
    virtual void onSetupFragment();
    std::vector<GPPtr<GLTexture> > mResources;
    std::vector<int> mResoucePos;
    GPPtr<GLProgram> mProgram;
    std::map<int, float> mUniforms;
};
#endif
