#ifndef DISPLAY_XMLSHADER_H
#define DISPLAY_XMLSHADER_H

#include "math/GLMatrix4.h"
#include "utils/GLLock.h"
#include "utils/RefCount.h"
#include "head.h"
#include <string>

class GLProgram:public RefCount
{
    public:
        GLProgram();
        GLProgram(const std::string& vertex, const std::string& frag);
        void load(const std::string& vertex, const std::string& frag);
        void load(const char* vertex, const char* frag);
        void loadFiles(const char* vertex, const char* frag);
        virtual ~GLProgram();

        inline unsigned int id() const{return mId;}

        /*These API must be called in openGL context Thread*/
        CONTEXT_API bool init();
        CONTEXT_API void destroy();
        CONTEXT_API void use();
        CONTEXT_API void useSingle() const;
        CONTEXT_API int attr(const char* name) const;
        CONTEXT_API int uniform(const char* name) const;
        CONTEXT_API static void setMatrix(const GLMatrix4& matrix, int id);
        CONTEXT_API static void setUniform(int value, int id);
        CONTEXT_API static void setUniform(float value, int id);
        CONTEXT_API static void setUniform(float* value, int n, int id);
    protected:
        unsigned int mId;
        bool mInit;
    private:
        std::string mVertex;
        std::string mFragment;
        unsigned int mVertId;
        unsigned int mFragId;

        GLLock mLock;
};



#endif
