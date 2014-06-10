#ifndef FRAGMENT_TEXTURE2D_H
#define FRAGMENT_TEXTURE2D_H

#include "interface/IFragmentFunction.h"
#include "interface/IBitmap.h"

IRasterizatedVarying* texture2D(IBitmap* sample, IRasterizatedVarying* texcord);

#endif
