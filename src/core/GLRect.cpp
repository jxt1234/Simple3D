#include "core/GLRect.h"
void GLRect::enLarge(int _l, int _t, int _r, int _b)
{
    if (l > _l || l < 0) l = _l;
    if (t > _t || t < 0) t = _t;
    if (r < _r || r < 0) r = _r;
    if (b < _b || b < 0) b = _b;
}

