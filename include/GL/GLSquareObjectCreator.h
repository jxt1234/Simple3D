#include "GLObject.h"
#include "GLTexture.h"
#include "GLvboBuffer.h"

class GLSquareObjectCreator:public GLObjectCreator
{
    public:
        struct SquarePara
        {
            GLObject* basic;
            GLTexture* t;
            int verId;
            int texId;
            int normaliId;
        };
        GLSquareObjectCreator();
        virtual ~GLSquareObjectCreator();
        virtual CONTEXT_API GLObject* vCreate(std::istream* parameter=NULL) const;
        virtual void vGetInfo(std::ostream& output) const;
    private:
        void _init();
        GPPtr<GLvboBuffer> mVertex;
        GPPtr<GLvboBuffer> mTexcord;
        GPPtr<GLvboBuffer> mNormal;
};
