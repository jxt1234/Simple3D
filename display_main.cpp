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
#include "GL/GLTextureWork.h"
#include "GL/GLAutoFbo.h"
#include "GL/GLDrawWork.h"
#include "GL/GLMultiPassDrawWork.h"
#include "GL/GLFixScaleDrawWork.h"
#define PI 3.141592654
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

GPPtr<IGLDrawWork> gTreatWorks;
GPPtr<IGLDrawWork> gOriginWorks;
GPPtr<GLTexture> gTexture;
GPPtr<GLBmp> gBmp;
#define ENLARGE_P 2.03

static string loadFiles(const char* name)
{
    ifstream vertex(name);
    ostringstream vertex_s;
    vertex_s << vertex.rdbuf();
    return vertex_s.str();
}

static IGLDrawWork* init_origin()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/Shallow.vex";
    const char* origin_frag = "/Users/jiangxiaotang/Documents/shader/basic.fra";
    return new GLDrawWork(loadFiles(vertex), loadFiles(origin_frag));
}

static IGLDrawWork* init_shallow_origin()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/Shallow_origin.vex";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/Shallow_origin.fra";
    map<string, float> firstunifom;
    firstunifom.insert(make_pair("texelWidth", 1.0/gBmp->width()));
    firstunifom.insert(make_pair("texelHeight", 1.0/gBmp->height()));
    firstunifom.insert(make_pair("filterRatio", 1.0));
    firstunifom.insert(make_pair("pixelNumAUnit", 1.0));
    return new GLDrawWork(loadFiles(vertex), loadFiles(frag));
}

static IGLDrawWork* init_filter()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/Gauss.vex";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/Gauss.fra";
    map<string, float> firstunifom;
    map<string, float> secondunifom;
    firstunifom.insert(make_pair("texelWidth", 1.0/gBmp->width()));
    firstunifom.insert(make_pair("texelHeight", 0.0));
    secondunifom.insert(make_pair("texelWidth", 0.0));
    secondunifom.insert(make_pair("texelHeight", 1.0/gBmp->height()));
    vector<GPPtr<IGLDrawWork> > works;
    works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &firstunifom));
    works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &secondunifom));
    return new GLMultiPassDrawWork(works);
}

static IGLDrawWork* init_treat()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/Shallow.vex";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/Shallow.fra";
    const char* frag2 = "/Users/jiangxiaotang/Documents/shader/ShallowFirst.fra";
    
    map<string, float> firstunifom;
    firstunifom.insert(make_pair("texelWidth", 1.0/gBmp->width()));
    firstunifom.insert(make_pair("texelHeight", 0.0));
    firstunifom.insert(make_pair("filterRatio", 1.0));
    
    map<string, float> secondunifom;
    
    secondunifom.insert(make_pair("texelWidth", 0.0));
    secondunifom.insert(make_pair("texelHeight", 1.0/gBmp->height()));
    secondunifom.insert(make_pair("filterRatio", 1.0));
    
    vector<GPPtr<IGLDrawWork> > works;
    works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag2), &secondunifom));
    works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &firstunifom));

    return new GLMultiPassDrawWork(works);
}


static void init()
{
    gOriginWorks = init_origin();
    //gTreatWorks = init_treat();
    //gTreatWorks = init_shallow_origin();
    gTreatWorks = init_filter();
    gTexture = new GLTexture;
    gTexture->upload(gBmp->pixels(), gBmp->getWidth(), gBmp->getHeight());
}
static void display(void)
{
    // GPCLOCK;
    float texpoints[] = {
        0.0,0.0,
        0.0,1.0,
        1.0,0.0,
        1.0,1.0
    };
    GLvboBuffer texcord(texpoints, 2, 4, GL_TRIANGLE_STRIP);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /*Treated picture*/
    {
        float points[] = {
            -1.0, -1.0,
            -1.0, 1.0,
            -1.0+2.0/ENLARGE_P, -1.0,
            -1.0+2.0/ENLARGE_P, 1.0
        };
        GLvboBuffer temp(points, 2, 4, GL_TRIANGLE_STRIP);
        gTreatWorks->onDraw(gTexture.get(), &temp, &texcord);
    }
    /*Origin picture*/
    {
        float points[] = {
            0.0, -1.0,
            0.0, 1.0,
            2.0/ENLARGE_P, -1.0,
            2.0/ENLARGE_P, 1.0
        };
        GLvboBuffer temp(points, 2, 4, GL_TRIANGLE_STRIP);
        gOriginWorks->onDraw(gTexture.get(), &temp, &texcord);
    }
    glutSwapBuffers();
}

int main(int argc, char* argv[])
{
    gBmp = new GLBmp;
    //gBmp->loadPicture("/Users/jiangxiaotang/Documents/shader/forge.jpg");
    gBmp->loadPicture("/Users/jiangxiaotang/Documents/shader/testpic1.jpg");
    //gBmp->loadPicture("/Users/jiangxiaotang/Documents/shader/pic1.jpg");
    glutInit(&argc, argv);                            // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);        // Set display mode
    glutInitWindowPosition(50,100);                    // Set top-left display window position
    int windoww = gBmp->width()*ENLARGE_P;
    int windowh = gBmp->height();
    const float maxw = 960.0;
    if (windoww > maxw)
    {
        float ratio = windoww/maxw;
        windoww = maxw;
        windowh = windowh/ratio;
    }
    glutInitWindowSize(windoww, windowh);                    // set display window width and height
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
