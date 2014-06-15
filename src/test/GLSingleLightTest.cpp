#include "test/GLTest.h"
#include "core/GLBmp.h"
#include "fragment/GLLightFunction.h"
#include "fragment/GLTexture2D.h"
#include "core/GLRasterization.h"
#include "vertex/GL_position.h"
#include "fragment/GL_FragTexcord.h"
#include "fragment/GL_FragPosition.h"
#include "utils/debug.h"
#include "vertex/GL_texcord.h"
#include "fragment/GL_vPosition.h"
#include "vertex/GLVectorVarying.h"
#include "vertex/GL_Normal.h"
#include "math/GLSphere.h"
#include "core/GLDepthBuffer.h"

using namespace GLVector;
using namespace std;

#define PI 3.141592653


static void _limit(float* color)
{
    if (color[0]>1) color[0] =1;
    if (color[1]>1) color[1] =1;
    if (color[2]>1) color[2] =1;
    if (color[3]>1) color[3] =1;
}

class GLSingleLightTest:public GLTest
{
    public:
        virtual void run()
        {
            int w = 720;
            int h = 1280;
            GLDepthBuffer depth(w, h);
            GLBmp GLTexture("ori.png");
            GLBmp output(w, h);
            GLBmp output_origin(w, h);
            gl_MaterialParameters m;
            m.shininess = 0.3;
            setVec4(0.3, 0.3, 0.3, 0.3, m.emission);
            setVec4(0.3, 0.3, 0.3, 0.3, m.ambient);
            setVec4(0.3, 0.3, 0.3, 0.3, m.diffuse);
            setVec4(0.3, 0.3, 0.3, 0.3, m.specular);
            setVec4(0.3, 0.3, 0.3, 0.3, m.sceneColor);
            vec3 eyepos;
            vec3 lightpos;
            setVec3(0,0,300, eyepos);
            setVec3(300,300,1000,lightpos);
            GLMatrix4 projection = GLMatrix4::projection(-300, 300, -300, 300, 100, 400, w/1.0/h);
            //GLMatrix4 projection = GLMatrix4::ortho(-300, 300, -300, 300, 100, 400, w/1.0/h);

            GLSphere sphere(150,0,0,-350);
            GLRectArea area;
            area.x1 = 0;
            area.x2 = 1;
            area.y1 = 0;
            area.y2 = 1;
            area.ux = 0.01;
            area.uy = 0.01;
            //Vertex
            GL_position p;
            GL_Normal normal;
            //Texcorder
            GL_texcord tex;
            GLCSVertexGenerate(&p, &normal, &tex, &sphere, &area, 0);
            p.reshape();
            p.transform(projection);
            p.normalize();
            GL_FragPosition f;
            GL_FragTexcord ftex(GLTexture.getWidth(), GLTexture.getHeight());
            GL_vPosition vPostion;
            GL_vPosition vNormal;
            //Arranging
            vector<IVarying*> inputs;
            inputs.push_back(&p);
            inputs.push_back(&tex);
            inputs.push_back(&p);//To get vPostion
            inputs.push_back(&normal);
            vector<IRasterizatedVarying*> outputs;
            outputs.push_back(&f);
            outputs.push_back(&ftex);
            outputs.push_back(&vPostion);
            outputs.push_back(&vNormal);
            GLRasterization(inputs, outputs, w, h, &depth);
            IRasterizatedVarying* basicColor = GLTexture2D(&GLTexture, &ftex);
            IRasterizatedVarying* finalColor = GLSingleLightFunction(&m, lightpos, eyepos, &vPostion, &vNormal, basicColor);
            for (int i=0; i<finalColor->size(); ++i)
            {
                float* color = finalColor->load(i);
                _limit(color);
                float* color2 = basicColor->load(i);
                _limit(color2);
                float* pos = f.load(i);
                int x = pos[0];
                int y = pos[1];
                if (x>=w) x=w-1;
                if (y>=h) y=h-1;
                GLColor c;
                c.r = color[0]*255;
                c.g = color[1]*255;
                c.b = color[2]*255;
                c.a = color[3]*255;
                output.setColor(c, x, y);
                c.r = color2[0]*255;
                c.g = color2[1]*255;
                c.b = color2[2]*255;
                c.a = color2[3]*255;
                output_origin.setColor(c, x, y);
            }
            output.save("output/light.png");
            output_origin.save("output/before_light.png");


            delete basicColor;
            delete finalColor;
        }
        GLSingleLightTest(){}
        virtual ~GLSingleLightTest(){}
};


static GLTestRegister<GLSingleLightTest> a("SingleLightTest");
