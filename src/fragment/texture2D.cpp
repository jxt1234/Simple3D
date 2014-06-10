#include "fragment/texture2D.h"
#include "fragment/GL_FragColor.h"

using namespace std;

class texture2DCompute:public IFragmentFunction
{
    public:
        texture2DCompute(IBitmap* pic):mPic(pic)
        {
            mHeight = pic->getHeight();
            mWidth = pic->getWidth();
        }
        virtual ~texture2DCompute(){}
        virtual void unitcompute(std::vector<float*> input, vector<float*> output)
        {
            float* pos = input[0];
            int x = pos[0]*mWidth;
            int y = pos[1]*mHeight;
            if (x>mWidth-1) x = mWidth-1;
            if (x<0) x=0;
            if (y>mHeight-1) y = mHeight-1;
            if (y<0) y=0;
            GLColor c = mPic->getColor(x, y);
            float* r = output[0];
            r[0]=(c.r/255.0);
            r[1]=(c.g/255.0);
            r[2]=(c.b/255.0);
            r[3]=(c.a/255.0);
        }
    private:
        IBitmap* mPic;
        int mWidth;
        int mHeight;
};

IRasterizatedVarying* texture2D(IBitmap* sample, IRasterizatedVarying* texcord)
{
    texture2DCompute t(sample);
    IRasterizatedVarying* result = new GL_FragColor;
    result->alloc(texcord->size());
    vector<IRasterizatedVarying*> inputs;
    vector<IRasterizatedVarying*> outputs;
    inputs.push_back(texcord);
    outputs.push_back(result);
    t.compute(outputs, inputs);
    return result;
}
