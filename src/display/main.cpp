#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "display/GLProgram.h"
#include "display/GLvboBuffer.h"
#include "display/GLTexture.h"
#include "display/GLCurveObject.h"
#include "vertex/GL_position.h"
#include "vertex/GL_texcord.h"
#include "vertex/GL_Normal.h"
#include "math/GLMatrix4.h"
#include "math/GLSphere.h"
#include "core/GLRasterization.h"
#include "utils/debug.h"
#include "core/GLBmp.h"
#include <fstream>


using namespace std;


GLTexture* gTexture = NULL;
GLvboBuffer* gTexBuffer = NULL;

static GLCurveObject* initCurve()
{
    GLCurveObject* result = new GLCurveObject();
    result->setTexture(gTexture);
    result->setVBO(gTexBuffer);
    result->setFormula(string("sin(2*3.141592654*u)"), string("cos(2*3.141592654*u)"), string("-v"));
    //result->setScale(100.0,200.0);
    return result;
}

static void init()
{
    gTexture = new GLTexture();
    GLBmp b;
    b.loadPicture("ori.png");
    gTexture->upload(b.pixels(), b.getWidth(), b.getHeight());
    GLSphere sphere(150, 0, 0, -350);
    GLRectArea area;
    area.set(0,0,1,1,0.01,0.01);
    //Vertex
    GL_Normal normal;
    //Texcorder
    GL_texcord tex;
    GL_position p;
    GLCSVertexGenerate(&p, &normal, &tex, &sphere, &area, 0);
    gTexBuffer = new GLvboBuffer(&tex);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLMatrix4 projection = GLMatrix4::projection(-1, 1, -1, 1, 1, 400, 1);
    GLMatrix4 transform;
    static GLCurveObject* obj = NULL;
    if (obj == NULL)
    {
        obj = initCurve();
    }
    obj->onDraw(transform, projection);
    glutSwapBuffers(); 
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);                            // Initialize GLUT 
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);        // Set display mode 
    glutInitWindowPosition(50,100);                    // Set top-left display window position 
    glutInitWindowSize(500, 500);                    // set display window width and height 
    glutCreateWindow("An Example OpenGL Program");    // Create display window 

    glewInit();
    init();
    glutDisplayFunc(display);                        // Send graphics to display window 

    glutMainLoop();                                    // Display everything and wait 
    return 1;
}
