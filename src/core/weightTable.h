#define WEIGTNUMBER 3
#include "interface/IRasterizatedVarying.h"
class weightTable
{
    public:
        //Basic
        weightTable(int w, int h, float* p1, float* p2, float* p3);
        virtual ~weightTable();
        void Rasterization();
        void rasterize(IRasterizatedVarying* output, float* x1, float* x2, float* x3);
        void generate(IRasterizatedVarying* data, int sta);
        /*Make this equation: z = k1*pos[0]+k2*pos[1]+k3*/
        void computeWeight(float& k1, float& k2, float& k3, float z1, float z2, float z3);
    protected:
        //Assert that the w is a 3-float data
        inline void getWeight(float* w, float* pos)
        {
            w[0] = w11*pos[0] + w12*pos[1] + w13;
            w[1] = w21*pos[0] + w22*pos[1] + w23;
            w[2] = 1 - w[0] -w[1];
        }
        float w11;
        float w12;
        float w13;
        float w21;
        float w22;
        float w23;
    private:
        float* mData;
        int mSize;
};
