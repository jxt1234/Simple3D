#include <GL/glew.h>
#include <GL/glut.h>
#include <FreeImage.h>
#include "test/GLTest.h"
int main(int argc, char* argv[])
{
    srand(time(NULL));
    FreeImage_Initialise(TRUE);
	//TODO Divide GPU Test to another file
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);        // Set display mode 
    glutInitWindowPosition(50,100); 
    glutInitWindowSize(500, 500); 
    glutCreateWindow("An Example OpenGL Program");

	glewInit();
    GLTestSuit::run();

    FreeImage_DeInitialise();
}
