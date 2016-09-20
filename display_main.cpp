#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GLUT/GLUT.h>
#include "GL/GLProgram.h"
#include "GL/GLLightScene.h"
#include "GL/GLBasic3DObject.h"
#include "GL/GLvboBuffer.h"
#include "GL/GLTexture.h"
#include "GL/GLCurveObject.h"
#include "GL/GLLightCurveObj.h"
#include "GL/GLBezier.h"
#include "BasicFunctionDeter.h"
#include "vertex/GL_position.h"
#include "vertex/GL_texcord.h"
#include "vertex/GL_Normal.h"
#include "math/GLMatrix4.h"
#include "math/GLSphere.h"
#include "core/GLRasterization.h"
#include "utils/GLDebug.h"
#include "core/GLBmp.h"
#include <fstream>
#define PI 3.141592654


using namespace std;

static GLObject* gObj = NULL;

GLObject* initObject()
{
    std::ifstream input("/Users/jiangxiaotang/fbx/test");
    GLBasicMesh* mesh = GLBasicMesh::load(input);
    GPPtr<GLBmp> texture = new GLBmp("/Users/jiangxiaotang/fbx/tank.fbm/AM84_011_K2_Diff.jpg");
    
    auto obj = new GLBasic3DObject(mesh, texture.get());
    obj->onPrepare();
    
    GLMatrix4 projection = GLMatrix4::projection(-50, 50, -50, 50, 10, 400, 1);
    GLMatrix4 transform;
    GLMatrix4 model;
    auto total = model*transform*projection;
    for (int i=0; i<mesh->size(); ++i)
    {
        float in[4];
        for (int j=0; j<4; ++j)
        {
            in[j] = mesh->get()[i].vertex[j];
        }
        in[3] = 1.0f;
        float out[4];
        total.transform(out, in);
        
//        printf("%.2f,%.2f,%.2f,%.2f -> %.2f,%.2f,%.2f,%.2f\n", in[0], in[1], in[2], in[3], out[0], out[1], out[2], out[3]);
        
    }
    delete mesh;
    return obj;
}

static void init()
{
    gObj = initObject();
}

static void display(void)
{
    //glDisable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //GLMatrix4 projection;
    GLMatrix4 projection = GLMatrix4::projection(-50, 50, -50, 50, 10, 400, 1);
    GLMatrix4 transform;
    GLMatrix4 model;

	static float a = 0.01;
    //model.setScale(a*10, a*10, a*10);
//	transform.setRotate(-a,0.1*a,0.3*a,a);
	a+=0.01;
    gObj->onDraw(model, transform, projection);
    glutSwapBuffers(); 
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);                            // Initialize GLUT 
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);        // Set display mode
    glutInitWindowPosition(50,100);                    // Set top-left display window position 
    glutInitWindowSize(500, 500);                    // set display window width and height 
    glutCreateWindow("An Example OpenGL Program");    // Create display window 

    init();
    glutDisplayFunc(display);                        // Send graphics to display window 
	glutIdleFunc(display);

    glutMainLoop();                                    // Display everything and wait 
    return 1;
}
