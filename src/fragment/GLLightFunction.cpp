#include "fragment/GLLightFunction.h"
#include "fragment/GL_FragColor.h"
#include <math.h>
#include "utils/GLDebug.h"

using namespace GLVector;
using namespace std;


/*vec3 L = normalize(gl_LightSource[0].position.xyz - v); 
 vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)
 vec3 R = normalize(-reflect(L,N)); 
 
 //calculate Ambient Term:
 vec4 Iamb = gl_FrontLightProduct[0].ambient;
 
 //calculate Diffuse Term:
 vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);
 
 // calculate Specular Term:
 vec4 Ispec = gl_FrontLightProduct[0].specular 
                   * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);
 // write Total Color:
 gl_FragColor = gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec; */

/*Light per-pixels, from http://blog.csdn.net/hippig/article/details/7484931*/
class GLSingleLightFunctionClass:public IFragmentFunction
{
    public:
        GLSingleLightFunctionClass(gl_MaterialParameters* _m, float* _lightpos, float* _E):m(_m), lightpos(_lightpos), E(_E)
        {
            normalize(E);
        }
        virtual ~GLSingleLightFunctionClass(){}
        //unitcompute 
        virtual void unitcompute(std::vector<float*> input, std::vector<float*> output)
        {
            float* Iamb = m->ambient;
            float* basicColor = input[2];
            float* color = output[0];
            multi(color, Iamb, basicColor, 4);
            GLVector::minus(L, input[0], lightpos, 3);
            normalize(L);
            float* N = input[1];
            normalize(N);
            float p = dot(N, L);
            if (p<0) p = 0;
            vec4 Idiff;
            linear(color, color, 1.0, m->sceneColor, 1.0, 4);
            multi(Idiff, basicColor, m->diffuse, 4);
            linear(color, color, 1.0, Idiff, p, 4);
            vec3 R;
            reflect(R, L, N);
            float dotRE=-dot(R, E);
            if (dotRE > 0)
            {
                float* Ispec = m->specular;;
                linear(color, Ispec, pow(dotRE, m->shininess), color, 1.0, 4);
            }
        }
        gl_MaterialParameters* m;
        float* E;
        float* lightpos;
        vec3 L;//For compute
};

IRasterizatedVarying* GLSingleLightFunction(gl_MaterialParameters* m, vec3 lightpos, vec3 eyepos, IRasterizatedVarying* position, IRasterizatedVarying* normal, IRasterizatedVarying* basicColor)
{
    assert(normal->size()==basicColor->size());
    GL_FragColor* result = new GL_FragColor;
    result->alloc(normal->size());
    GLSingleLightFunctionClass func(m, lightpos, eyepos);
    vector<IRasterizatedVarying*> output;
    output.push_back(result);
    vector<IRasterizatedVarying*> input;
    input.push_back(position);
    input.push_back(normal);
    input.push_back(basicColor);
    func.compute(output, input);
    return result;
}
