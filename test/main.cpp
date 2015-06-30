#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "test/GLTest.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    GLTestSuit::run();

}
