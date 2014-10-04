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
            GLVector::vec3 lightpos;
            GLVector::vec3 mEyePos;
            GLVector::vec4 emission;
            GLVector::vec4 ambient;
            GLVector::vec4 diffuse;
            GLVector::vec4 specular;
            GLVector::vec4 sceneColor;
            float shininess;
        };
        //n means the light's number
        GLLightScene(int n=1);
        virtual ~GLLightScene();
        void setLightNumber(int n);
        void setLightPos(int n, GLVector::vec3 pos);
        //As GLObject
        virtual void onGenerateShader(std::ostream& vertex, std::ostream& frag) const;
        virtual void onPrepare();
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
        GLLightAttr mLights;
        std::vector<GPPtr<GLObject> > mObjs;
        std::vector<GPPtr<GLObject> >::iterator mIter;
        friend class GLLightObject;

};
