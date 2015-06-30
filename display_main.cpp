#include <sstream>
#include <fstream>
#ifndef __APPLE__
#include <GL/glew.h>
#include <GL/glut.h>
#else
#include <GLUT/GLUT.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GL/GLProgram.h"
#include "GL/GLvboBuffer.h"
#include "GL/GLTexture.h"
#include "utils/debug.h"
#include "core/GLBmp.h"
#include "utils/GP_Clock.h"
#define PI 3.141592654
#include <math.h>
#include "math/FormulaTree.h"
#include "math/BasicFunctionDeter.h"

static void init()
{
    
}
static void display(void)
{
    // GPCLOCK;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glutSwapBuffers();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);                            // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);        // Set display mode 
    glutInitWindowPosition(50,100);                    // Set top-left display window position 
    glutInitWindowSize(500, 500);                    // set display window width and height 
    glutCreateWindow("An Example OpenGL Program");    // Create display window 
#ifndef __APPLE__
    glewInit();
#endif
    init();
    glutDisplayFunc(display);                        // Send graphics to display window 
    glutIdleFunc(display);

    glutMainLoop();                                    // Display everything and wait 
    return 1;
}
