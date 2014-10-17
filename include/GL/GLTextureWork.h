#ifndef GL_GLTEXTUREWORK_H
#define GL_GLTEXTUREWORK_H
#include "head.h"
#include "GLWork.h"
#include "GLProgram.h"
#include "GLTexture.h"
#include "GLvboBuffer.h"
#include <vector>
class GLTextureWork:public RefCount
{
    public:
        GLTextureWork();
        GLTextureWork(const char* vertex, const char* frag);
        virtual ~GLTextureWork();
        //Must in GL Thread
        virtual bool onPrepare();
        virtual void onDestroy();
        virtual void run(GLTexture* dst, std::vector<GLTexture*> sources);
        virtual bool onGenerateShader(std::ostream& vertex, std::ostream& frag) const {return false;}

        void setProgram(GPPtr<GLProgram> pro) {mShader = pro;}
        static void DefaultVertex(std::ostream& vertex);
        virtual void onUse(GLTexture* dst, std::vector<GLTexture*> sources, GLProgram* shader) {}
    private:
        GPPtr<GLProgram> mShader;
};
#endif
