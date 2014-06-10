#ifndef INTERFACE_VERTEXFUNCTION_H
#define INTERFACE_VERTEXFUNCTION_H

#include "head.h"
#include "IVarying.h"
class IVertexFunction
{
    public:
        virtual void unitcompute(std::vector<float*> input, std::vector<float*> output) = 0;
        INTERFACE(IVertexFunction);
        void compute(std::vector<IVarying*> outputs, std::vector<IVarying*> inputs)
        {
            assert(!inputs.empty());
            int _size = inputs[0]->size();
            /*Debug begin*/
            for (int i=0; i<inputs.size(); ++i)
            {
                assert(NULL!=inputs[i]);
            }
            for (int i=1; i<inputs.size(); ++i)
            {
                assert(_size == inputs[i]->size());
            }
            /*Debug end*/
            std::vector<float*> input(inputs.size(), NULL);
            std::vector<float*> output(outputs.size(), NULL);
            for (int i=0; i<_size; ++i)
            {
                for (int j=0; j<inputs.size(); ++j)
                {
                    input[j] = (inputs[j]->load(i));
                }
                for (int j=0; j<outputs.size(); ++j)
                {
                    output[j] = outputs[j]->load(i);
                }
                this->unitcompute(input, output);
            }
        }
};

#endif
