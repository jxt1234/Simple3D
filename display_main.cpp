#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GL/GLProgram.h"
#include "GL/GLvboBuffer.h"
#include "GL/GLTexture.h"
#include "GL/GLCurveObject.h"
#include "GL/GLBezier.h"
#include "vertex/GL_position.h"
#include "vertex/GL_texcord.h"
#include "vertex/GL_Normal.h"
#include "math/GLMatrix4.h"
#include "math/GLSphere.h"
#include "core/GLRasterization.h"
#include "utils/debug.h"
#include "core/GLBmp.h"
#include <fstream>
#define PI 3.141592654


using namespace std;

static GLCurveObject* initCurve()
{
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

    GLCurveObject* result = new GLCurveObject();
    result->setTexture(texture);
    result->setVBO(texBuffer);
    result->setFormula(string("(1.0+v/2.0*cos(u/2.0))*cos(u)"), string("(1.0+v/2.0*cos(u/2.0))*sin(u)"), string("v/2.0*sin(u/2.0)"));
    //result->setFormula(string("1.0"), string("10*u"), string("-10.0*v"));
    result->setScale(2*PI,2);
    result->setOffset(0,-0.5);
    glEnable(GL_DEPTH_TEST);
    return result;
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

static void init()
{
    //gObj = initCurve();
	gObj = initBezier();
}

static void display(void)
{
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //GLMatrix4 projection = GLMatrix4::projection(-10, 10, -10, 10, 10, 400, 1);
    GLMatrix4 projection;
    GLMatrix4 transform;
	static float a = 0;
	transform.setRotate(0,1,0,a);
	a+=0.001;
    gObj->onDraw(transform, projection);
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
