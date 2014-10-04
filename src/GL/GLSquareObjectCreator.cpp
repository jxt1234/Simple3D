#include "GL/GLSquareObjectCreator.h"
#include "GL/GLTexture1Obj.h"
#include <string.h>
#include <stdio.h>
#include <istream>
GLSquareObjectCreator::GLSquareObjectCreator()
{
    _init();
}
GLSquareObjectCreator::~GLSquareObjectCreator()
{
}

void GLSquareObjectCreator::_init()
{
    if (NULL != mVertex.get()) return;
    float ver[4*6*6];
    float nor[3*6*6];
    float tex[2*6*6];
    for (int i=0; i<6; ++i)
    {
        int fix = i%3;
        int vary1 = (i+1)%3;
        int vary2 = (i+2)%3;
        float fixValue = (float)(2*(i%2) - 1);
        for (int j=0; j<6; ++j)
        {
            float* _ver = ver + (i*6+j)*4;
            float* _nor = nor + (i*6+j)*3;
            float* _tex = tex + (i*6+j)*2;

            int basic = 2*(j/3)-1;
            int mid = (j%3)%2;
            float v1 = basic;
            if (mid) v1 = -basic;
            float v2 = -v1;
            if (j%3==0) v2 = v1;
            _ver[fix] = fixValue;
            _ver[vary1] =v1;
            _ver[vary2] =v2;
            _ver[3] = 1.0;

            _tex[0] = (v1+1.0)/2.0;
            _tex[1] = (v2+1.0)/2.0;

            for (int k=0; k<3; ++k)
            {
                _nor[k] = 0.0;
            }
            _nor[fix] = fixValue;
        }
    }
    for (int i=0;i<6;++i)
    {
        for (int j=0; j<6; ++j)
        {
            float* _ver = ver + (i*6+j)*4;
            printf("%f, %f, %f, %f\n", _ver[0], _ver[1], _ver[2], _ver[3]);
        }
        printf("\n");
    }
    mVertex = new GLvboBuffer(ver, 4, 6*6);
    mNormal = new GLvboBuffer(nor, 3, 6*6);
    mTexcord = new GLvboBuffer(tex, 2, 6*6);
}

GLObject* GLSquareObjectCreator::vCreate(std::istream* parameter) const
{
    assert(NULL!=parameter);
    //TODO Support multi Textures
    SquarePara p;
    std::istream& is = *parameter;
    is.read((char*)(&p), sizeof(p));

    (p.t)->addRef();
    GPPtr<GLTexture> t = p.t;

    (p.basic)->addRef();
    GPPtr<GLObject> basic = p.basic;

    GLTexture1Obj* obj = new GLTexture1Obj(basic);
    obj->set(t, mVertex, mTexcord, mNormal, p.verId, p.texId, p.normaliId);
    return obj;
}
void GLSquareObjectCreator::vGetInfo(std::ostream& output) const
{
}
