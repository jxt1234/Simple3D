#include "head.h"

CONTEXT_CLASS class GLAutoProgram
{
    public:
        GLAutoProgram(int proId);
        ~GLAutoProgram();
    private:
        int mId;
        int mPrevious;
};
