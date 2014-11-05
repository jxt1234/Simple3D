#include "GLCurveObject.h"
#include "math/IFunctionDeter.h"
class GLLightCurveObj:public GLCurveObject
{
    public:
        GLLightCurveObj(const IFunctionDeter* deter);
        virtual ~GLLightCurveObj();

        void getNormalCurve(std::ostream& vertex, const std::string& xf, const std::string& yf, const std::string& zf) const;
    private:
        virtual void vGetVertex(std::ostream& vertex, const std::string& xf, const std::string& yf, const std::string& zf) const;
        virtual void vGetFramgent(std::ostream& frag, const std::string& x, const std::string& y, const std::string& z) const;

        const IFunctionDeter* sDeter;
};
