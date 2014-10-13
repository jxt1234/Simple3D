#include <GL/glew.h>
#include <GL/glut.h>
#include <FreeImage.h>
#include <GL/GLContext.h>
#include "test/GLTest.h"
int main()
{
    int p=1;
    srand(time(NULL));
    FreeImage_Initialise(TRUE);
    GLContext::init();
    GLTestSuit::run();

    FreeImage_DeInitialise();
}
