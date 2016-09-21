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
#include <sstream>
#include "3d/CCBundle3D.h"
#define PI 3.141592654


using namespace std;

static GLObject* gObj = NULL;

GLObject* initObject()
{
    GPPtr<Bundle3D::Buffer> buffer;
    std::ifstream inputc3d("/Users/jiangxiaotang/fbx/tank.c3b");
    std::ostringstream output3d;
    output3d << inputc3d.rdbuf();
    buffer = new Bundle3D::Buffer(output3d.str().c_str(), output3d.str().size());
    auto bundle3D = Bundle3D::createBundle();
    bundle3D->load(buffer.get());
    MeshDatas rmeshDatas;
    bundle3D->loadMeshDatas(rmeshDatas);
    
    MaterialDatas rmaterialDatas;
    bundle3D->loadMaterials(rmaterialDatas);
    
    NodeDatas nodeDatas;
    bundle3D->loadNodes(nodeDatas);
    
    
    auto obj = new GLBasic3DObject(nodeDatas, rmeshDatas, rmaterialDatas);
    Bundle3D::destroyBundle(bundle3D);
    obj->onPrepare();
    
    return obj;
}

static void init()
{
    gObj = initObject();
}

static void display(void)
{
    //glDisable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //GLMatrix4 projection;
    GLMatrix4 projection = GLMatrix4::projection(-50, 50, -50, 50, 10, 1000, 1);
    GLMatrix4 V;
    GLMatrix4 model;

	static float a = 0.01;
	//model.setRotate(-a,0.1*a,0.3*a,a);
    model.setRotate(0.0,1.0,0.0,a);
	a+=0.01;
    
    V.setTranslate(0, 0, -500);
    
    gObj->onDraw(model, V, projection);
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
