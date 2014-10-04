#include "math/GLMatrix4.h"

class GLTransformer:public RefCount
{
    public:
        GLTransformer(){}
        GLTransformer(const GLMatrix4& matrix):mMatrix(matrix){}
        virtual ~GLTransformer(){}
        //TODO Add operator to change matrix
        inline const GLMatrix4& get() const {return mMatrix;}
    private:
        GLMatrix4 mMatrix;
};
