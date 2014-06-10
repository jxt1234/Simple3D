#include "display/texture.h"

texture::texture()
{
    mId = 0;
}

texture::~texture()
{
    OPENGL_ASSERT(mId == 0);
}
