#ifndef CORE_GLCOLOR_H
#define CORE_GLCOLOR_H

#define GLCOLOR(a, r, g, b) (((a)<<24)+((r)<<16)+((g)<<8)+(b));

typedef unsigned char uchar;
struct GLColor
{
    uchar a;
    uchar r;
    uchar g;
    uchar b;
};

struct GLFloatColor
{
    float a;
    float r;
    float g;
    float b;
};

#endif
