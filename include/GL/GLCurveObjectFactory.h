#ifndef GL_GLCURVEOBJECTFACTORY_H
#define GL_GLCURVEOBJECTFACTORY_H
class GLCurveObject;
class IFunctionDeter;
class GLCurveObjectFactory
{
    public:
        typedef enum
        {
            NONE,
            LIGHT,
            BICUBIC
        }TYPE;
        static GLCurveObject* create(TYPE t = NONE);
    private:
        static IFunctionDeter* gDeter;
};
#endif
