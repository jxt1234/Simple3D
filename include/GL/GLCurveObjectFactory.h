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
