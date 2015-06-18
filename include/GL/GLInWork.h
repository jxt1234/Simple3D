#ifndef GL_GLINWORK_H
#define GL_GLINWORK_H
#include "head.h"
#include "core/GLBmp.h"
#include "GL/GLTexture.h"
#include "GL/GLProgram.h"
#include <vector>
CONTEXT_CLASS class GLInWork:public RefCount
{
public:
    /*If vertex/frag is NULL, use default shader*/
    GLInWork(const char* vertex, const char* frag, std::vector<GLBmp*> resouces);
    virtual ~GLInWork();
    static void setDefaultVertexShader(const char* vertex);
    static void setDefaultFragmentShader(const char* frag);

    void beforedraw();
    void draw();
    void release();
    
private:
    virtual void onSetupVertex();
    virtual void onSetupFragment();

    std::vector<GPPtr<GLTexture> > mResources;
    std::vector<int> mResoucePos;
    GPPtr<GLProgram> mProgram;
    
    static std::string gDefaultVertex;
    static std::string gDefaultFrag;
    
};
#endif
