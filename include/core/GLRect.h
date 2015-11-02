#ifndef CORE_GLRECT_H
#define CORE_GLRECT_H
struct GLRect
{
    int l;
    int r;
    int t;
    int b;
    bool valid() const {return l>=0 && r>=l && t>=0 && b>=t;}
    void enLarge(int _l, int _t, int _r, int _b);
};
#endif
