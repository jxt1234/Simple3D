//
//  GLFixScaleDrawWork.cpp
//  simple3d
//
//  Created by jiangxiaotang on 15/7/4.
//  Copyright (c) 2015年 jiangxiaotang. All rights reserved.
//

#include <stdio.h>
#include "GL/GLFixScaleDrawWork.h"

static const char* gDefaultVertex ="\n"
"attribute vec2 position;\n"
"attribute vec2 inputTextureCoordinate;\n"
"varying vec2 textureCoordinate;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position,1.0,1.0);\n"
"    textureCoordinate = inputTextureCoordinate;\n"
"}\n"
;


static const char* gDefaultFrag = "\n"
"varying vec2 textureCoordinate;\n"
"uniform sampler2D buffer;\n"
"void main(void)\n"
"{\n"
"    gl_FragColor = texture2D(buffer, textureCoordinate);\n"
"}\n"
;


GLFixScaleDrawWork::GLFixScaleDrawWork(GPPtr<IGLDrawWork> origin, int w, int h)
{
    GLASSERT(NULL!=origin.get());
    GLASSERT(w>0&&h>0);
    mWork = origin;
    mTexture = new GLTexture;
    mTexture->upload(NULL, w, h);
    mTexture->setFilter(true);
    const float defaultVex[] = {
        -1.0, -1.0,
        -1.0, 1.0,
        1.0, -1.0,
        1.0, 1.0
    };
    mVs = new GLvboBuffer(defaultVex, 2, 4, GL_TRIANGLE_STRIP);
    const float defaultTex[] = {
        0.0,0.0,
        0.0,1.0,
        1.0,0.0,
        1.0,1.0
    };
    mTs = new GLvboBuffer(defaultTex, 2, 4, GL_TRIANGLE_STRIP);
    mProgram = new GLProgram(gDefaultVertex, gDefaultFrag);
    mProgram->init();
}
GLFixScaleDrawWork::~GLFixScaleDrawWork()
{
    
}
void GLFixScaleDrawWork::onDraw(GLTexture** src, int num, GLvboBuffer* vs, GLvboBuffer* ts)
{
    GLASSERT(NULL!=src);
    GLASSERT(NULL!=vs);
    GLASSERT(NULL!=ts);
    GLASSERT(1 == num);
    GLASSERT(NULL!=src[0]);
    {
        GLAutoFbo __fbo(*mTexture);
        mProgram->use();
        src[0]->use();
        mVs->use(mProgram->attr("position"));
        mTs->use(mProgram->attr("inputTextureCoordinate"));
        mVs->draw();
    }
    GLTexture* mp = mTexture.get();
    mWork->onDraw(&mp, 1, vs, ts);
}
int GLFixScaleDrawWork::vMap(double* parameters, int n)
{
    return mWork->vMap(parameters, n);
}
