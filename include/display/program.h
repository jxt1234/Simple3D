#ifndef DISPLAY_XMLSHADER_H
#define DISPLAY_XMLSHADER_H

#include <iostream>
#include <vector>
#include "head.h"

class program
{
    public:
        program();
        program(const std::string& vertex, const std::string& frag);
        void load(const std::string& vertex, const std::string& frag);
        void loadFiles(const char* vertex, const char* frag);
        virtual ~program();

        inline unsigned int id(){return mId;}

        /*These API must be called in openGL context Thread*/
        CONTEXT_API void init();
        CONTEXT_API void destory();
        CONTEXT_API void use();
        CONTEXT_API int attr(const char* name);
        CONTEXT_API int uniform(const char* name);
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
