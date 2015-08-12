#include "utils/GLOnceWork.h"
void GLOnceWork::readyToRun()
{
}
bool GLOnceWork::threadLoop()
{
    (*mF)();
    return false;
}
void GLOnceWork::destroy()
{
}
