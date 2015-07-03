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
#define PI 3.141592654
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

GPPtr<GLTexture> gTexture;
GPPtr<GLTexture> gMidTexture;
GPPtr<GLProgram> gDisplayProgram;
GPPtr<GLProgram> gFirstProgram;
GPPtr<GLProgram> gOriginProgram;
GPPtr<GLBmp> gBmp;
#define ENLARGE_P 2.03

static void init_origin()
{
    gOriginProgram = new GLProgram;
    gOriginProgram->loadFiles("/Users/jiangxiaotang/Documents/shader/Shallow.vex", "/Users/jiangxiaotang/Documents/shader/basic.fra");
    gOriginProgram->init();
}

static void init()
{
    init_origin();
    ifstream vertex("/Users/jiangxiaotang/Documents/shader/Shallow.vex");
    ifstream frag("/Users/jiangxiaotang/Documents/shader/Shallow.fra");
    ifstream frag2("/Users/jiangxiaotang/Documents/shader/ShallowFirst.fra");
    ostringstream vertex_s;
    ostringstream frag_s;
    ostringstream frag_s2;
    vertex_s << vertex.rdbuf();
    string vertex_string = vertex_s.str();
    frag_s << frag.rdbuf();
    gDisplayProgram = new GLProgram(vertex_s.str().c_str(), frag_s.str().c_str());
    gDisplayProgram->init();
    frag_s2 << frag2.rdbuf();
    gFirstProgram = new GLProgram(vertex_string.c_str(), frag_s2.str().c_str());
    gFirstProgram->init();
    gTexture = new GLTexture;
    gTexture->upload(gBmp->pixels(), gBmp->getWidth(), gBmp->getHeight());
    gMidTexture = new GLTexture;
    gMidTexture->upload(NULL, gBmp->getWidth(), gBmp->getHeight());
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
    {
        float points[] = {
            -1.0, -1.0,
            -1.0, 1.0,
            1.0, -1.0,
            1.0, 1.0
        };
        GLvboBuffer temp(points, 2, 4, GL_TRIANGLE_STRIP);
        GLAutoFbo __f(*(gMidTexture.get()));
        gFirstProgram->use();
        gTexture->use();
        glUniform1f(glGetUniformLocation(gFirstProgram->id(), "texelWidth"), 2.0/gTexture->width());
        glUniform1f(glGetUniformLocation(gFirstProgram->id(), "texelHeight"), 0.0);
        glUniform1f(glGetUniformLocation(gFirstProgram->id(), "filterRatio"), 1.0);
        OPENGL_CHECK_ERROR;
        temp.use(gFirstProgram->attr("position"));
        texcord.use(gFirstProgram->attr("inputTextureCoordinate"));
        temp.draw();
    }
    /*Treated picture*/
    {
        float points[] = {
            -1.0, -1.0,
            -1.0, 1.0,
            -1.0+2.0/ENLARGE_P, -1.0,
            -1.0+2.0/ENLARGE_P, 1.0
        };
        GLvboBuffer temp(points, 2, 4, GL_TRIANGLE_STRIP);
        gDisplayProgram->use();
        temp.use(gDisplayProgram->attr("position"));
        texcord.use(gDisplayProgram->attr("inputTextureCoordinate"));
        gMidTexture->use();
        glUniform1f(glGetUniformLocation(gDisplayProgram->id(), "texelWidth"), 0.0);
        glUniform1f(glGetUniformLocation(gDisplayProgram->id(), "texelHeight"), 2.0/gTexture->height());
        glUniform1f(glGetUniformLocation(gDisplayProgram->id(), "filterRatio"), 1.0);
        OPENGL_CHECK_ERROR;
        temp.draw();
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
        gOriginProgram->use();
        temp.use(gOriginProgram->attr("position"));
        gTexture->use();
        texcord.use(gOriginProgram->attr("inputTextureCoordinate"));
        temp.draw();
        
    }
    glutSwapBuffers();
}

int main(int argc, char* argv[])
{
    gBmp = new GLBmp;
    //    gBmp->loadPicture("/Users/jiangxiaotang/Documents/shader/forge.jpg");
    gBmp->loadPicture("/Users/jiangxiaotang/Documents/shader/pic1.jpg");
    glutInit(&argc, argv);                            // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);        // Set display mode
    glutInitWindowPosition(50,100);                    // Set top-left display window position
    glutInitWindowSize(gBmp->width()*ENLARGE_P, gBmp->height());                    // set display window width and height
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
