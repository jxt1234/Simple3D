#include "test/GLTest.h"
#include "core/GLRasterization.h"
#include "vertex/GL_position.h"
#include "fragment/GL_FragPosition.h"
#include "utils/debug.h"
#include "core/GLBmp.h"
#include "vertex/GL_texcord.h"
#include "fragment/GL_FragTexcord.h"

using namespace std;

class GLRasterBasicTest:public GLTest
{
    public:
        virtual void run()
        {
            int w = 720;
            int h = 1280;
            GL_position* p = new GL_position;
            p->addPoint(-0.5, 0.5, 0.5, 1);
            p->addPoint(0.5, 1, 0.5, 1);
            p->addPoint(-0.5, -1, 0.5, 1);
            p->addPoint(-1.0, 0.5, 0.5, 1);
            p->addPoint(0.5, 1, 0.5, 1);
            p->addPoint(-0.4, 1, 0.5, 1);
            p->addPoint(1.0, 0.5, 0.5, 1);
            p->addPoint(-0.5, -1, 0.5, 1);
            p->addPoint(1.0, -1, 0.5, 1);
            //Texcorder
            GL_texcord* tex = new GL_texcord;
            tex->addPoint(0.0, 1.0);
            tex->addPoint(1.0, 1.0);
            tex->addPoint(0.0, 0.0);
            tex->addPoint(1.0, 1.0);
            tex->addPoint(0.0, 1.0);
            tex->addPoint(1.0, 0.0);
            tex->addPoint(1.0, 1.0);
            tex->addPoint(0.0, 1.0);
            tex->addPoint(1.0, 0.0);
            GL_FragPosition* f = new GL_FragPosition;
            GLBmp texture("ori.png");
            GL_FragTexcord* ftex = new GL_FragTexcord(texture.getWidth(), texture.getHeight());
            //
            vector<IVarying*> inputs;
            inputs.push_back(p);
            inputs.push_back(tex);
            vector<IRasterizatedVarying*> outputs;
            outputs.push_back(f);
            outputs.push_back(ftex);
            GLRasterization(inputs, outputs, w, h);
            GLBmp b(w, h);
            GLColor c;
            c.r = 0;
            c.g = 0;
            c.b = 0;
            c.a = 0;
            b.clear(c);
            c.r = 255;
            for (int i=0; i<f->size(); ++i)
            {
                float* pos = f->load(i);
                vector<int> texc = ftex->loadInt(i);
                int x = pos[0];
                int y = pos[1];
                if (x<0|| y<0)
                {
                    FUNC_PRINT(x);
                    FUNC_PRINT(y);
                }
                if (x>=w) x=w-1;
                if (y>=h) y=h-1;
                int u = texc[0];
                int v = texc[1];
                if (u<0|| v<0)
                {
                    FUNC_PRINT(u);
                    FUNC_PRINT(v);
                }
                b.setColor(texture.getColor(u, v), x, y);
            }
            b.save("output/raster.png");
            delete p;
            delete tex;
            delete f;
            delete ftex;
        }
        GLRasterBasicTest(){}
        virtual ~GLRasterBasicTest(){}
};

static GLTestRegister<GLRasterBasicTest> a("rasterBasicTest");
