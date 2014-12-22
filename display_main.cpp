#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GL/GLProgram.h"
#include "GL/GLvboBuffer.h"
#include "GL/GLTexture.h"
#include "GL/GLCurveObject.h"
#include "GL/GLCurveObjectFactory.h"
#include "GL/GLBezier.h"
#include "GL/GLLightScene.h"
#include "vertex/GL_position.h"
#include "vertex/GL_texcord.h"
#include "vertex/GL_Normal.h"
#include "math/GLMatrix4.h"
#include "math/GLSphere.h"
#include "core/GLRasterization.h"
#include "utils/debug.h"
#include "core/GLBmp.h"
#include "utils/GP_Clock.h"
#define PI 3.141592654
#include <math.h>
#include "math/FormulaTree.h"
#include "math/BasicFunctionDeter.h"


using namespace std;

static GLObject* initCurve(GLCurveObjectFactory::TYPE t)
{
    string x = string("(1.0+v/2.0*cos(u/2.0))*cos(u)");
    string y = string("(1.0+v/2.0*cos(u/2.0))*sin(u)");
    string z = string("v/2.0*sin(u/2.0)");

    std::ifstream is("function.txt");
    BasicFunctionDeter basic(is);
    is.close();
    FormulaTree _x(&basic), _y(&basic), _z(&basic);
    _x.setFormula(x);
    _y.setFormula(y);
    _z.setFormula(z);

    ostringstream __x, __y, __z;
    _x.expand(__x);
    _y.expand(__y);
    _z.expand(__z);

    GLTexture* texture = new GLTexture();
    GLBmp b;
    b.loadPicture("input.jpg");
    texture->upload(b.pixels(), b.getWidth(), b.getHeight());
    GLEmptyCurveSurface s;
    GLRectArea area;
    area.set(0,0,1,1,0.01,0.01);
    GL_Normal normal;
    GL_texcord tex;
    GL_position p;
    GLCSVertexGenerate(&p, &normal, &tex, &s, &area, 0);
    GLvboBuffer* texBuffer = new GLvboBuffer(&tex);

    GLCurveObject* result = NULL;
    result = GLCurveObjectFactory::create(t);
    result->setTexture(texture);
    result->setVBO(texBuffer);
    //result->setFormula(x, y, z);
    result->setFormula(__x.str(), __y.str(), __z.str());
    result->setScale(2*PI,2);
    result->setOffset(0,-0.5);

    GPPtr<GLObject> res = result;
    GLLightScene* scene = new GLLightScene;
    scene->onPrepare();
    scene->vAddObject(res);
    scene->setEyePos(0, 0, -10.0);
    scene->setLightPos(0, 0, 0, 100);
    return scene;
}

static GLObject* gObj = NULL;

GLObject* initBezier()
{
    GLBezier* res = new GLBezier(100, 3.0);
    res->addPoint(0.0,-1.0,1);
    res->addPoint(-0.4,0.0,1);
    res->addPoint(0.2,1.0,1);
    res->onPrepare();
    return res;
}

GLObject* initLight()
{
    GLLightScene* scene = new GLLightScene;
    scene->onPrepare();
    GLTexture* texture = new GLTexture();
    GLBmp b;
    b.loadPicture("input.jpg");
    texture->upload(b.pixels(), b.getWidth(), b.getHeight());
    ostringstream os;
    os.write((char*)(&texture), sizeof(GLTexture*));
    istringstream input(os.str());
    GPPtr<GLObject> square = scene->vCreate(&input);
    scene->vAddObject(square);
    scene->setEyePos(0, 0, -5.0);
    scene->setLightPos(0, 0, 0, 100);
    return scene;
}

static void init()
{
    gObj = initCurve(GLCurveObjectFactory::LIGHT);
    //gObj = initBezier();
    //gObj = initLight();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0);
}

static void display(void)
{
    // GPCLOCK;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLMatrix4 projection = GLMatrix4::projection(-2, 2, 2, -2, 3, 400, 1);
    //GLMatrix4 projection;
    GLMatrix4 transform;
    GLMatrix4 view;
    float p = -10;
    view.setTranslate(0,0,p);
    static float a = 0;
    transform.setRotate(0,1,0,a);

    //transform.setTranslate(0,1.0, 0);
    a+=0.05;
    int angle = (a/PI*180);
    angle = angle%360;
    //printf("angle = %d\n", angle);
    gObj->onDraw(transform, view, projection);
    glutSwapBuffers(); 
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);                            // Initialize GLUT 
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);        // Set display mode 
    glutInitWindowPosition(50,100);                    // Set top-left display window position 
    glutInitWindowSize(500, 500);                    // set display window width and height 
    glutCreateWindow("An Example OpenGL Program");    // Create display window 

    glewInit();
    init();
    glutDisplayFunc(display);                        // Send graphics to display window 
    glutIdleFunc(display);

    glutMainLoop();                                    // Display everything and wait 
    return 1;
}
