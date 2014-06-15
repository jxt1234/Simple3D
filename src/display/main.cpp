#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "display/program.h"
#include "display/vboBuffer.h"
#include "display/texture.h"
#include "vertex/GL_position.h"
#include "vertex/GL_texcord.h"
#include "vertex/GL_Normal.h"
#include "math/GLMatrix4.h"
#include "math/GLSphere.h"
#include "core/GLRasterization.h"
#include "utils/debug.h"


using namespace std;

float gPos[] = {-0.9,1.0,0.4,0.5,-1.0,-0.5};

program gProgram;
texture gTexture;
vboBuffer* gBuffer = NULL;
vboBuffer* gTexBuffer = NULL;

static void init()
{
    gProgram.loadFiles("glsl/basic.vertex", "glsl/basic.frag");
    gTexture.init();
    const int w = 50; const int h = 50;
    unsigned int* a  = new unsigned int[w*h];
    for (int i=0; i<w; ++i)
    {
        for (int j=0; j<h; ++j)
        {
            a[i*h+j] = i+j*j;
        }
    }
    gTexture.upload(a, w, h);
    delete [] a;
    GLMatrix4 projection = GLMatrix4::projection(-300, 300, -300, 300, 100, 400, w/1.0/h);
    GLSphere sphere(150, 0, 0, -350);
    GLRectArea area;
    area.set(0,0,1,1,0.01,0.01);
    //Vertex
    GL_Normal normal;
    //Texcorder
    GL_texcord tex;
    GL_position p;
    GLCSVertexGenerate(&p, &normal, &tex, &sphere, &area, 0);
    assert(p.size() == tex.size());
    p.reshape();
    p.transform(projection);
    p.normalize();
    gBuffer = new vboBuffer(&p);
    gTexBuffer = new vboBuffer(&tex);
}

static void display(void)
{
    glLoadIdentity(); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gProgram.use();
    int pid = gProgram.attr("pos");
    int tid = gProgram.attr("tex");
    gTexBuffer->use(tid);
    gBuffer->use(pid);
    assert(gBuffer->size() == gTexBuffer->size());
    gTexture.use();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, gBuffer->size());
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
