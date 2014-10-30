#ifndef GL_GLLIGHTSCENE_H
#define GL_GLLIGHTSCENE_H
#include <vector>
#include <map>
#include "math/GLVector.h"
#include "GLScene.h"
#include "GLProgram.h"
class GLLightScene:public GLScene, GLObjectCreator
{
    public:
        //TODO Divide scene attribute and object attribute
        struct GLLightAttr
        {
            GLVector::vec4 lightpos;
            GLVector::vec4 lightColor;
            GLVector::vec4 eyepos;
            GLVector::vec4 ambientColor;
            float ka;
            float kd;
            float ks;
            float ns;
        };
        //n means the light's number
        GLLightScene(int n=1);
        virtual ~GLLightScene();
        void setEyePos(float x, float y, float z);
        void initDefaultAttr(GLLightAttr& attr);
        void setLightNumber(int n);
        void setLightPos(int n, float x, float y, float z);
        //As GLObject
        virtual void onGenerateShader(std::ostream& vertex, std::ostream& frag) const;
        virtual bool onPrepare();
        /*As GLObjectManager*/
        virtual void vAddObject(GPPtr<GLObject> obj);
        virtual void vRemoveObject(GPPtr<GLObject> obj);
        virtual void vRemoveAll();
        virtual const GLObjectCreator* vGetCreator() const {return this;}
        /*As creator*/
        virtual GLObject* vCreate(std::istream* parameter=NULL) const;
        virtual void vGetInfo(std::ostream& output) const;
    protected:
        /*As GLObjectIterator*/
        virtual GPPtr<GLObject> vCurrent() const{ return *mIter;}
        virtual void vNext() {mIter++;}
        virtual bool vEnd() const {return mIter == mObjs.end();}
        virtual void vRewind() {mIter = mObjs.begin();}
    private:
        class GLLightObject:public GLObject
        {
            public:
                GLLightObject(const GLProgram& pro, const GLLightAttr& attr);
                virtual ~GLLightObject();
                virtual void onDraw(const GLMatrix4& M, const GLMatrix4& V, const GLMatrix4& P);
            private:
                const GLProgram& mProgram;
                const GLLightAttr& mAttr;
        };
        GPPtr<GLProgram> mProgram;
        GLLightAttr mAttr;
        std::vector<GPPtr<GLObject> > mObjs;
        std::vector<GPPtr<GLObject> >::iterator mIter;
        friend class GLLightObject;
};
#endif
