#include "GL/GLBitmapWorkFactory.h"
GLBitmapWorkFactory GLBitmapWorkFactory::gFactory;

GLBitmapWorkFactory& GLBitmapWorkFactory::get()
{
    return gFactory;
}

void GLBitmapWorkFactory::printMethods(std::ostream& os)
{
    CREATERS& c = gFactory.mCreator;
    CREATERS::iterator it = c.begin();
    for (;it!=c.end(); it++)
    {
        os << it->first<<std::endl;
        it->second->vDetail(os);
    }
}

GLBitmapWork* GLBitmapWorkFactory::create(const char* name, std::istream* input)
{
    GLBitmapWorkFactory& f = GLBitmapWorkFactory::get();
    return f._create(name, input);
}

GLBitmapWork* GLBitmapWorkFactory::_create(const char* name, std::istream* input)
{
    if (NULL==name) return NULL;
    CREATERS::iterator i = mCreator.find(std::string(name));
    if (i!=mCreator.end())
    {
        return (i->second)->vCreate(input);
    }
    return NULL;
}

GLBitmapWorkFactory::GLBitmapWorkFactory()
{
}

GLBitmapWorkFactory::~GLBitmapWorkFactory()
{
    for (CREATERS::iterator i=mCreator.begin(); i!=mCreator.end(); i++)
    {
        delete i->second;
        i->second = NULL;
    }
}
