#include <GL/glew.h>
#include <GL/glut.h>
#include <FreeImage.h>
#include "test/GLTest.h"
int main()
{
    int p=1;
    srand(time(NULL));
    FreeImage_Initialise(TRUE);
	//TODO Divide GPU Test to another file
    glutInit(&p, NULL);
    glutCreateWindow("An Example OpenGL Program");

	glewInit();
    GLTestSuit::run();

    FreeImage_DeInitialise();
}
