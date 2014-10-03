#include "math/GLMatrix4.h"

class GLTransformer:public RefCount
{
    public:
        GLTransformer(){}
        virtual ~GLTransformer(){}
        inline const GLMatrix4& get() const {return mMatrix;}
    private:
        GLMatrix4 mMatrix;
};
