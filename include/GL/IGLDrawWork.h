#ifndef GL_IGLDRAWWORK_H
#define GL_IGLDRAWWORK_H
#include "head.h"
#include "GLvboBuffer.h"
#include "GLTexture.h"
class IGLDrawWork:public RefCount
{
public:
    IGLDrawWork() = default;
    virtual ~IGLDrawWork() = default;
    /*Main interface*/
    virtual void onDraw(GLTexture** src, int n, GLvboBuffer* vs, GLvboBuffer* ts) = 0;
    
    /*All parameters is in [0,1), set self parameters by these, if parameters is NULL, don't do anything just return the number of parameters needed*/
    virtual size_t vMap(double* parameters, size_t n) = 0;
    
    
    void drawSingle(GLTexture* src, GLvboBuffer* vs, GLvboBuffer* ts);
private:
    IGLDrawWork(const IGLDrawWork&) = default;
    IGLDrawWork& operator=(const IGLDrawWork&) = default;
};
#endif
