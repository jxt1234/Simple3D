#include "vertex/GL_position.h"
#include "utils/debug.h"
using namespace std;


void GL_position::reshape()
{
    int size = this->size();
    for (int i=0; i<size; ++i)
    {
        float* p = this->load(i);
        p[3] = 1;
    }
}
