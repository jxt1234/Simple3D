#ifndef GL_GLMULTIPASSDRAWWORK_H
#define GL_GLMULTIPASSDRAWWORK_H
#include "IGLDrawWork.h"
#include "GLProgram.h"
#include "GLTexture.h"
#include "GLvboBuffer.h"
#include <vector>
#include <string>
CONTEXT_CLASS class GLMultiPassDrawWork:public IGLDrawWork
{
public:
    GLMultiPassDrawWork(const std::vector<GPPtr<IGLDrawWork> >& works);
    virtual ~GLMultiPassDrawWork();
    virtual void onDraw(GLTexture** src, int num, GLvboBuffer* vs, GLvboBuffer* ts);
    virtual size_t vMap(double* parameters, size_t n);
private:
    std::vector<GPPtr<IGLDrawWork> > mWorks;
    /*Two texture, for ping-pong*/
    GPPtr<GLTexture> mFirstTexture;
    GPPtr<GLTexture> mSecondTexture;
    
    /*use vs and ts in the last pass, use mVs and mTs before*/
    GPPtr<GLvboBuffer> mVs;
    GPPtr<GLvboBuffer> mTs;
    
    std::vector<int> mOffset;
};
#endif
