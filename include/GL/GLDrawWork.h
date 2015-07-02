#ifndef GL_GLDRAWWORK_H
#define GL_GLDRAWWORK_H
#include "head.h"
#include "core/GLBmp.h"
#include "GL/GLTexture.h"
#include "GL/GLProgram.h"
#include "GL/GLvboBuffer.h"
#include <string>
#include <vector>
/*DrawWork For Single Work*/
class GLDrawWork:public RefCount
{
public:
    /*If vertex/frag is NULL, use default shader*/
    GLDrawWork(const std::string& vertex, const std::string& frag, std::vector<GLBmp*> resouces);
    virtual ~GLDrawWork();
    virtual void onDraw(int srcid, int w, int h, GLvboBuffer* vs, GLvboBuffer* ts);
    virtual int vMap(int* parameters) {return 0;}
    
protected:
    virtual void onSetupVertex();
    virtual void onSetupFragment();
    std::vector<GPPtr<GLTexture> > mResources;
    std::vector<int> mResoucePos;
    GPPtr<GLProgram> mProgram;
    bool mUseOes;
    
};
#endif
