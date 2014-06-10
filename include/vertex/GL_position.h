#ifndef VERTEX_GL_POSITION_H
#define VERTEX_GL_POSITION_H
#include "interface/IVarying.h"
#include "GLVectorVarying.h"
#include <vector>
class GL_position:public GLVectorVarying
{
    public:
        GL_position(){}
        void addVector(const std::vector<float> input)
        {
            addPoint(input[0], input[1], input[2], 1);
        }
        //Use to set the 4th element be 1, so it can be seen as a vec3
        void reshape();
        virtual ~GL_position(){}
    protected:
};


#endif
