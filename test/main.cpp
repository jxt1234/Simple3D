#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <FreeImage.h>
#include "test/GLTest.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    FreeImage_Initialise(TRUE);
    GLTestSuit::run();

    FreeImage_DeInitialise();
}
