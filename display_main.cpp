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
#include "GL/GLTreeDrawWork.h"
#define PI 3.141592654
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

GPPtr<IGLDrawWork> gTreatWorks;
GPPtr<IGLDrawWork> gOriginWorks;
GPPtr<GLTexture> gTexture;
GPPtr<GLTexture> gTreatedTexture;
GPPtr<GLBmp> gBmp;
#define ENLARGE_P 2.03

static string loadFiles(const char* name)
{
    ifstream vertex(name);
    GLASSERT(!vertex.fail());
    ostringstream vertex_s;
    vertex_s << vertex.rdbuf();
    return vertex_s.str();
}

static IGLDrawWork* init_origin()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/Shallow.vex";
    const char* origin_frag = "/Users/jiangxiaotang/Documents/shader/basic.fra";
    return new GLDrawWork(loadFiles(vertex), loadFiles(origin_frag), NULL);
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
    return new GLDrawWork(loadFiles(vertex), loadFiles(frag), &firstunifom);
}
static IGLDrawWork* init_skin_nolocal()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/skin_nonlocal.fra";
    map<string, float> firstunifom;
    firstunifom.insert(make_pair("texelWidth", 1.0/gBmp->width()));
    firstunifom.insert(make_pair("texelHeight", 1.0/gBmp->height()));
    map<string, float> secondunifom;
    secondunifom.insert(make_pair("texelWidth", 1.0/gBmp->width()));
    secondunifom.insert(make_pair("texelHeight", 0.0/gBmp->height()));
    vector<GPPtr<IGLDrawWork> > works;
    works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &firstunifom));
    //works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &secondunifom));
    return new GLMultiPassDrawWork(works);
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
    //return new GLFixScaleDrawWork(new GLMultiPassDrawWork(works), 1280, 720);
}

static IGLDrawWork* init_treat()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/ShallowOnePass.fra";
    
    map<string, float> firstunifom;
    firstunifom["texelWidth"] = 1.0/gBmp->width();
    firstunifom["texelHeight"] = 0.0;
    firstunifom["filterRatio"] = 1.0;
    firstunifom["sigma_c"] = 30.0;
    firstunifom["sigma_s"] = 0.1;
    
    map<string, float> secondunifom;
    secondunifom["texelWidth"] = 0.0;
    secondunifom["texelHeight"] = 1.0/gBmp->height();
    secondunifom["filterRatio"] = 1.0;
    secondunifom["sigma_c"] = 30.0;
    secondunifom["sigma_s"] = 0.1;
    
    vector<GPPtr<IGLDrawWork> > works;
    works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &secondunifom));
    works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &firstunifom));
    
    return new GLMultiPassDrawWork(works);
    //return new GLFixScaleDrawWork(new GLMultiPassDrawWork(works), 1280, 720);
}


static IGLDrawWork* init_skin_detect()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/Shallow.vex";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/skindetect.fra";
    return new GLDrawWork(loadFiles(vertex), loadFiles(frag), NULL);
}
static IGLDrawWork* init_filter_minsquare_detect()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/Shallow.vex";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/LSD.fra";
    map<string, float> secondunifom;
    secondunifom["texelWidth"] = 1.0/gBmp->width();
    secondunifom["texelHeight"] = 1.0/gBmp->height();
    return new GLDrawWork(loadFiles(vertex), loadFiles(frag), &secondunifom);
}

static IGLDrawWork* init_skin_onepass()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex";
    //const char* frag = "/Users/jiangxiaotang/Documents/shader/skin_filter_with_detect.fra";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/skin_lsd_onepass.fra";

    map<string, float> firstunifom;
    firstunifom["texelWidth"] = 1.0/gBmp->width();
    firstunifom["texelHeight"] = 1.0/gBmp->height();
    firstunifom["sigma_c"] = 30.0;
    firstunifom["sigma_s"] = 0.1;
    firstunifom["filterRatio"] = 1.0;
    IGLDrawWork* verWork = new GLDrawWork(loadFiles(vertex), loadFiles(frag), &firstunifom);
    return verWork;
}

static IGLDrawWork* init_guild_filter()
{
    map<string, float> p_uniform;
    p_uniform["texelWidth"] = 1.0/gBmp->width();
    p_uniform["texelHeight"] = 1.0/gBmp->height();
    map<string, float> c_uniform = p_uniform;
    c_uniform["thetha"] = 0.005;
    GPPtr<IGLDrawWork> p = new GLDrawWork(loadFiles("/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex"), loadFiles("/Users/jiangxiaotang/Documents/shader/guild_filter_slow_second.fra"), &p_uniform, NULL, 3);
    GPPtr<IGLDrawWork> l = new GLDrawWork(loadFiles("/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex"), loadFiles("/Users/jiangxiaotang/Documents/shader/guild_filter_slow_a.fra"), &c_uniform);
    GPPtr<IGLDrawWork> r = new GLDrawWork(loadFiles("/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex"), loadFiles("/Users/jiangxiaotang/Documents/shader/guild_filter_slow_b.fra"), &c_uniform);
    GLTreeDrawWork* tp = new GLTreeDrawWork(p);
    GPPtr<GLTreeDrawWork> lp = new GLTreeDrawWork(l);
    GPPtr<GLTreeDrawWork> rp = new GLTreeDrawWork(r);
    tp->addNode(NULL);
    tp->addNode(lp);
    tp->addNode(rp);
    return tp;
}

static IGLDrawWork* init_skin_detect_treat()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex";
    //const char* frag = "/Users/jiangxiaotang/Documents/shader/skin_filter_with_detect.fra";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/skin_with_lsd.fra";
    const char* frag2 = "/Users/jiangxiaotang/Documents/shader/skin_with_lsd_addbright.fra";

    map<string, float> firstunifom;
    firstunifom["texelWidth"] = 1.0/gBmp->width();
    firstunifom["texelHeight"] = 0.0;
    firstunifom["sigma_c"] = 30.0;
    firstunifom["sigma_s"] = 0.1;
    firstunifom["filterRatio"] = 1.0;

    map<string, float> secondunifom;
    secondunifom["texelHeight"] = 1.0/gBmp->height();
    secondunifom["filterRatio"] = 1.0;
    secondunifom["sigma_c"] = 30.0;
    secondunifom["sigma_s"] = 0.1;
    secondunifom["texelWidth"] = 0.0;

    vector<GPPtr<IGLDrawWork> > works;
    const int repeat = 0;
    GPPtr<IGLDrawWork> verWork = new GLDrawWork(loadFiles(vertex), loadFiles(frag), &secondunifom);
    GPPtr<IGLDrawWork> horWork = new GLDrawWork(loadFiles(vertex), loadFiles(frag), &firstunifom);
    GPPtr<IGLDrawWork> lastWork = new GLDrawWork(loadFiles(vertex), loadFiles(frag2), &firstunifom);
    works.push_back(verWork);
    for (int i=0; i<repeat; ++i)
    {
        works.push_back(horWork);
        works.push_back(verWork);
    }
    works.push_back(lastWork);
    return new GLMultiPassDrawWork(works);
    //return new GLFixScaleDrawWork(new GLMultiPassDrawWork(works), 1280, 720);
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
        gOriginWorks->drawSingle(gTreatedTexture.get(), &temp, &texcord);
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
        gOriginWorks->drawSingle(gTexture.get(), &temp, &texcord);
    }
    glutSwapBuffers();
}
static void init()
{
    gOriginWorks = init_origin();
    //gOriginWorks = init_treat();
    //gOriginWorks = init_skin_detect();
    //gTreatWorks = init_treat();
    //gTreatWorks = init_shallow_origin();
    //gTreatWorks = init_skin_detect();
    //gTreatWorks = init_filter_minsquare_detect();
    //gTreatWorks = init_filter();
    //gTreatWorks = init_skin_detect_treat();
    //gTreatWorks = init_skin_onepass();
    //gTreatWorks = init_skin_nolocal();
    gTreatWorks = init_guild_filter();
    gTexture = new GLTexture;
    gTexture->upload(gBmp->pixels(), gBmp->getWidth(), gBmp->getHeight());
    gTreatedTexture = new GLTexture;
    gTreatedTexture->upload(NULL, gBmp->getWidth(), gBmp->getHeight());
    // GPCLOCK;
    float texpoints[] = {
        0.0,0.0,
        0.0,1.0,
        1.0,0.0,
        1.0,1.0
    };
    GLvboBuffer texcord(texpoints, 2, 4, GL_TRIANGLE_STRIP);
    float points[] = {
        -1.0, -1.0,
        -1.0, 1.0,
        1.0, -1.0,
        1.0, 1.0
    };
    FUNC_PRINT(gBmp->getWidth());
    FUNC_PRINT(gBmp->getHeight());
    {
        GLAutoFbo __fbo(*gTreatedTexture);
        GLvboBuffer temp(points, 2, 4, GL_TRIANGLE_STRIP);
        gTreatWorks->drawSingle(gTexture.get(), &temp, &texcord);
    }
}

int main(int argc, char* argv[])
{
    gBmp = new GLBmp;
    //gBmp->loadPicture("/Users/jiangxiaotang/Documents/shader/forge.jpg");
    //gBmp->loadPicture("/Users/jiangxiaotang/Documents/shader/YuFamilyPhoto.jpg");
    //gBmp->loadPicture("/Users/jiangxiaotang/Documents/shader/skintest4.jpg");
    //gBmp->loadPicture("/Users/jiangxiaotang/Documents/shader/pic1.jpg");
    gBmp->loadPicture("/Users/jiangxiaotang/Data/Pictures/Pictures/0019667873730ec8401648.jpg");
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
    auto sta = clock();
    init();
    auto fin = clock();
    printf("Cost Time = %ld / %d\n", (fin-sta), CLOCKS_PER_SEC);
    glutDisplayFunc(display);                        // Send graphics to display window
    glutIdleFunc(display);
    
    glutMainLoop();                                    // Display everything and wait
    return 1;
}
