#ifndef DISPLAY_XMLSHADER_H
#define DISPLAY_XMLSHADER_H

#include <iostream>
#include <vector>
#include "math/GLMatrix4.h"
#include "head.h"

class GLProgram
{
    public:
        GLProgram();
        GLProgram(const std::string& vertex, const std::string& frag);
        void load(const std::string& vertex, const std::string& frag);
        void loadFiles(const char* vertex, const char* frag);
        virtual ~GLProgram();

        inline unsigned int id(){return mId;}

        /*These API must be called in openGL context Thread*/
        CONTEXT_API void init();
        CONTEXT_API void destroy();
        CONTEXT_API void use();
        CONTEXT_API int attr(const char* name);
        CONTEXT_API int uniform(const char* name);
        CONTEXT_API static void setMatrix(const GLMatrix4& matrix, int id);
        CONTEXT_API static void setUniform(int value, int id);
        CONTEXT_API static void setUniform(float value, int id);
    protected:
        unsigned int mId;
        bool mInit;
    private:
        char* mVertex;
        char* mFragment;
        unsigned int mVertId;
        unsigned int mFragId;
};



#endif
