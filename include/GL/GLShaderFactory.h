#ifndef GL_GLSHADERFACTORY_H
#define GL_GLSHADERFACTORY_H
#include <string>
class GLShaderFactory
{
    public:
        static const char* get(std::string name);
};
#endif
