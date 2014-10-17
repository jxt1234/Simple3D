#include "GL/GLMultiPassWork.h"
#include <sstream>
typedef std::vector<GPPtr<GLProgram> >::iterator ITER;

GLMultiPassWork::GLMultiPassWork()
{
}
GLMultiPassWork::~GLMultiPassWork()
{
}

/*FIXME Only the last time can we draw to the dst*/
void GLMultiPassWork::run(GLTexture* dst, std::vector<GLTexture*> sources)
{
    GLASSERT(NULL!=dst);
    GLASSERT(!sources.empty());
    GLASSERT(NULL!=sources.at(0));
    int odd = this->vGetStep()%2;
    GLTexture* current;
    GLTexture* next;
    GLTexture* src = sources.at(0);
    GPPtr<GLTexture> tempBuffer = new GLTexture;
    tempBuffer->upload(NULL, dst->width(), dst->height());
    if (odd)
    {
        current = dst;
        next = tempBuffer.get();
    }
    else
    {
        current = tempBuffer.get();
        next = dst;
    }
    this->vRewind();
    GLProgram* program = NULL;
    while (this->vCurrent(&program))
    {
        if (NULL!=program)
        {
            GPPtr<GLProgram> warp = program;
            program->addRef();//Spectial GPPtr
            setProgram(program);
        }
        std::vector<GLTexture*> _source(1, src);
        INHERIT::run(current, _source);
        /*Ping-Pong*/
        src = current;
        current = next;
        next = src;
        this->vNext();
        program = NULL;
    }
}

