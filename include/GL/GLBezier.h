#ifndef GL_GLBEZIER_H
#define GL_GLBEZIER_H
#include "GLObject.h"
#include <string>
#include <vector>
#include "GLProgram.h"
#include "GLTexture.h"
#include "GLvboBuffer.h"
#include "vertex/GL_position.h"
#include <ostream>
class GLBezier:public GLObject
{
    public:
        GLBezier(int precision = 100, float width = 1.0);
        virtual ~GLBezier();
        void addPoint(float x, float y, float z);
        int size() {return mControl->size();}
        void modify(int pos, float x, float y, float z);
        void setColor(float a, float r, float g, float b);
        void clean();
        void reset(int precision);
        virtual void onPrepare();
        virtual void onDraw(const GLMatrix4& transform, const GLMatrix4& projection);
    private:
        void _sync();
        void _genShader(std::ostream& vertex, std::ostream& frag);
        float mColor[4];
        GL_position* mControl;
        float* mParameter;
        GLProgram mProgram;
        GLvboBuffer* mVertex;
        float mWidth;
};
#endif
