#include "test/GLTest.h"
#include "vertex/GLVectorVarying.h"
#include "utils/debug.h"
#include "core/GLBmp.h"
#include "core/GLRasterization.h"
#include "vertex/GL_texcord.h"
#include "fragment/GL_FragTexcord.h"
#include "fragment/GL_FragPosition.h"
using namespace std;

class GLProjectionTest:public GLTest
{
    public:
        virtual void run()
        {
            int w = 720;
            int h = 1280;
            GLMatrix4 projection = GLMatrix4::projection(-300, 300, -300, 300, 100, 400);
            //FUNC_PRINT_ALL(projection.print().c_str(), s);
            GLVectorVarying p;
            p.addPoint(200, 200, 100, 1);
            p.addPoint(-100, 200, 100, 1);
            p.addPoint(200, 0, -100, 1);
            p.transform(projection);
            p.normalize();
            GL_texcord tex;
            tex.addPoint(0.0, 1.0);
            tex.addPoint(1.0, 1.0);
            tex.addPoint(0.0, 0.0);
            GL_FragPosition f;
            GLBmp texture("ori.png");
            GL_FragTexcord ftex(texture.getWidth(), texture.getHeight());
            vector<IVarying*> inputs;
            inputs.push_back(&p);
            inputs.push_back(&tex);
            vector<IRasterizatedVarying*> outputs;
            outputs.push_back(&f);
            outputs.push_back(&ftex);
            GLRasterization(inputs, outputs, w, h);
            GLBmp b(w, h);
            for (int i=0; i<f.size(); ++i)
            {
                float* pos = f.load(i);
                vector<int> texc = ftex.loadInt(i);
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
            b.save("output/GLProjectionTest.png");
        }
        GLProjectionTest(){}
        virtual ~GLProjectionTest(){}
};

static GLTestRegister<GLProjectionTest> a("ProjectionTest");
