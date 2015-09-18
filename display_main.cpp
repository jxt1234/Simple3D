#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#ifndef __APPLE__
#include <GL/glew.h>
#include <GL/glut.h>
#else
#include <GLUT/GLUT.h>
#endif
#include "GL/GLProgram.h"
#include "GL/GLvboBuffer.h"
#include "GL/GLTexture.h"
#include "utils/debug.h"
#include "core/GLBmp.h"
#include "utils/GP_Clock.h"
#include "GL/GLTextureWork.h"
#include "GL/GLAutoFbo.h"
#include "GL/GLDrawWork.h"
#include "GLHistogramEqualFilter.h"
#include "GL/GLMultiPassDrawWork.h"
#include "GL/GLFixScaleDrawWork.h"
#include "GL/GLTreeDrawWork.h"
#define PI 3.141592654
#include "GLGuideFilter.h"
#include "GLBrightFilter.h"
#include "GLLargeGPUFilter.h"
#include "GLSharpFilter.h"
#include "GLAutoStorage.h"
#include "GLKMeans.h"
#include "GLGMMModel.h"
#include <fstream>
#include "GLSampler.h"
#include "GLSharpFilter.h"
#include "GLTwoValueOperator.h"
#include "GLGraphicCut.h"
#include "GLGaussOperator.h"

using namespace std;

GPPtr<IGLDrawWork> gTreatWorks;
GPPtr<IGLDrawWork> gOriginWorks;
GPPtr<GLTexture> gTexture;
GPPtr<GLTexture> gTreatedTexture;
GPPtr<GLBmp> gBmp;
#define ENLARGE_P 2.03

static string loadFiles(const char* name)
{
    ifstream vertex(name);
    GLASSERT(!vertex.fail());
    ostringstream vertex_s;
    vertex_s << vertex.rdbuf();
    return vertex_s.str();
}

static IGLDrawWork* init_origin()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/Shallow.vex";
    const char* origin_frag = "/Users/jiangxiaotang/Documents/shader/basic.fra";
    return new GLDrawWork(loadFiles(vertex), loadFiles(origin_frag), NULL);
}

static IGLDrawWork* init_shallow_origin()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/Shallow_origin.vex";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/Shallow_origin.fra";
    map<string, float> firstunifom;
    firstunifom.insert(make_pair("texelWidth", 1.0/gBmp->width()));
    firstunifom.insert(make_pair("texelHeight", 1.0/gBmp->height()));
    firstunifom.insert(make_pair("filterRatio", 1.0));
    firstunifom.insert(make_pair("pixelNumAUnit", 1.0));
    return new GLDrawWork(loadFiles(vertex), loadFiles(frag), &firstunifom);
}
static IGLDrawWork* init_skin_nolocal()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/skin_nonlocal.fra";
    map<string, float> firstunifom;
    firstunifom.insert(make_pair("texelWidth", 1.0/gBmp->width()));
    firstunifom.insert(make_pair("texelHeight", 1.0/gBmp->height()));
    map<string, float> secondunifom;
    secondunifom.insert(make_pair("texelWidth", 1.0/gBmp->width()));
    secondunifom.insert(make_pair("texelHeight", 0.0/gBmp->height()));
    vector<GPPtr<IGLDrawWork> > works;
    works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &firstunifom));
    //works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &secondunifom));
    return new GLMultiPassDrawWork(works);
}

static IGLDrawWork* init_filter()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/Gauss.vex";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/Gauss.fra";
    map<string, float> firstunifom;
    map<string, float> secondunifom;
    firstunifom.insert(make_pair("texelWidth", 1.0/gBmp->width()));
    firstunifom.insert(make_pair("texelHeight", 0.0));
    secondunifom.insert(make_pair("texelWidth", 0.0));
    secondunifom.insert(make_pair("texelHeight", 1.0/gBmp->height()));
    vector<GPPtr<IGLDrawWork> > works;
    works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &firstunifom));
    works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &secondunifom));
    return new GLMultiPassDrawWork(works);
    //return new GLFixScaleDrawWork(new GLMultiPassDrawWork(works), 1280, 720);
}

static IGLDrawWork* init_treat()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/ShallowOnePass.fra";
    
    map<string, float> firstunifom;
    firstunifom["texelWidth"] = 1.0/gBmp->width();
    firstunifom["texelHeight"] = 0.0;
    firstunifom["filterRatio"] = 1.0;
    firstunifom["sigma_c"] = 30.0;
    firstunifom["sigma_s"] = 0.1;
    
    map<string, float> secondunifom;
    secondunifom["texelWidth"] = 0.0;
    secondunifom["texelHeight"] = 1.0/gBmp->height();
    secondunifom["filterRatio"] = 1.0;
    secondunifom["sigma_c"] = 30.0;
    secondunifom["sigma_s"] = 0.1;
    
    vector<GPPtr<IGLDrawWork> > works;
    works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &secondunifom));
    works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &firstunifom));
    
    return new GLMultiPassDrawWork(works);
    //return new GLFixScaleDrawWork(new GLMultiPassDrawWork(works), 1280, 720);
}


static IGLDrawWork* init_skin_detect()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/Shallow.vex";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/skindetect.fra";
    return new GLDrawWork(loadFiles(vertex), loadFiles(frag), NULL);
}
static IGLDrawWork* init_filter_minsquare_detect()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/Shallow.vex";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/LSD.fra";
    map<string, float> secondunifom;
    secondunifom["texelWidth"] = 1.0/gBmp->width();
    secondunifom["texelHeight"] = 1.0/gBmp->height();
    return new GLDrawWork(loadFiles(vertex), loadFiles(frag), &secondunifom);
}

static IGLDrawWork* init_skin_onepass()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex";
    //const char* frag = "/Users/jiangxiaotang/Documents/shader/skin_filter_with_detect.fra";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/skin_lsd_onepass.fra";
    
    map<string, float> firstunifom;
    firstunifom["texelWidth"] = 1.0/gBmp->width();
    firstunifom["texelHeight"] = 1.0/gBmp->height();
    firstunifom["sigma_c"] = 30.0;
    firstunifom["sigma_s"] = 0.1;
    firstunifom["filterRatio"] = 1.0;
    IGLDrawWork* verWork = new GLDrawWork(loadFiles(vertex), loadFiles(frag), &firstunifom);
    return verWork;
}

static IGLDrawWork* init_guild_filter()
{
    map<string, float> p_uniform;
    p_uniform["texelWidth"] = 1.0/gBmp->width();
    p_uniform["texelHeight"] = 1.0/gBmp->height();
    map<string, float> c_uniform = p_uniform;
    c_uniform["thetha"] = 0.005;
    p_uniform["filterRatio"] = 0.8f;
    GPPtr<IGLDrawWork> p = new GLDrawWork(loadFiles("/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex"), loadFiles("/Users/jiangxiaotang/Documents/shader/guild_filter_slow_second.fra"), &p_uniform, NULL, 3);
    GPPtr<IGLDrawWork> l = new GLDrawWork(loadFiles("/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex"), loadFiles("/Users/jiangxiaotang/Documents/shader/guild_filter_slow_a.fra"), &c_uniform);
    GPPtr<IGLDrawWork> r = new GLDrawWork(loadFiles("/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex"), loadFiles("/Users/jiangxiaotang/Documents/shader/guild_filter_slow_b.fra"), &c_uniform);
    GLTreeDrawWork* tp = new GLTreeDrawWork(p);
    GPPtr<GLTreeDrawWork> lp = new GLTreeDrawWork(l);
    GPPtr<GLTreeDrawWork> rp = new GLTreeDrawWork(r);
    tp->addNode(NULL);
    tp->addNode(lp);
    tp->addNode(rp);
    return tp;
}

static IGLDrawWork* init_skin_detect_treat()
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex";
    //const char* frag = "/Users/jiangxiaotang/Documents/shader/skin_filter_with_detect.fra";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/skin_with_lsd.fra";
    const char* frag2 = "/Users/jiangxiaotang/Documents/shader/skin_with_lsd_addbright.fra";
    
    map<string, float> firstunifom;
    firstunifom["texelWidth"] = 1.0/gBmp->width();
    firstunifom["texelHeight"] = 0.0;
    firstunifom["sigma_c"] = 30.0;
    firstunifom["sigma_s"] = 0.1;
    firstunifom["filterRatio"] = 1.0;
    
    map<string, float> secondunifom;
    secondunifom["texelHeight"] = 1.0/gBmp->height();
    secondunifom["filterRatio"] = 1.0;
    secondunifom["sigma_c"] = 30.0;
    secondunifom["sigma_s"] = 0.1;
    secondunifom["texelWidth"] = 0.0;
    
    vector<GPPtr<IGLDrawWork> > works;
    const int repeat = 0;
    GPPtr<IGLDrawWork> verWork = new GLDrawWork(loadFiles(vertex), loadFiles(frag), &secondunifom);
    GPPtr<IGLDrawWork> horWork = new GLDrawWork(loadFiles(vertex), loadFiles(frag), &firstunifom);
    GPPtr<IGLDrawWork> lastWork = new GLDrawWork(loadFiles(vertex), loadFiles(frag2), &firstunifom);
    works.push_back(verWork);
    for (int i=0; i<repeat; ++i)
    {
        works.push_back(horWork);
        works.push_back(verWork);
    }
    works.push_back(lastWork);
    return new GLMultiPassDrawWork(works);
    //return new GLFixScaleDrawWork(new GLMultiPassDrawWork(works), 1280, 720);
}


static void display(void)
{
    // GPCLOCK;
    float texpoints[] = {
        0.0,0.0,
        0.0,1.0,
        1.0,0.0,
        1.0,1.0
    };
    GLvboBuffer texcord(texpoints, 2, 4, GL_TRIANGLE_STRIP);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /*Origin picture*/
    {
        float points[] = {
            -1.0, -1.0,
            -1.0, 1.0,
            -1.0+2.0/ENLARGE_P, -1.0,
            -1.0+2.0/ENLARGE_P, 1.0
        };
        GLvboBuffer temp(points, 2, 4, GL_TRIANGLE_STRIP);
        gOriginWorks->drawSingle(gTexture.get(), &temp, &texcord);
    }
    /*Treated picture*/
    {
        float points[] = {
            0.0, -1.0,
            0.0, 1.0,
            2.0/ENLARGE_P, -1.0,
            2.0/ENLARGE_P, 1.0
        };
        GLvboBuffer temp(points, 2, 4, GL_TRIANGLE_STRIP);
        gOriginWorks->drawSingle(gTreatedTexture.get(), &temp, &texcord);
    }
    glutSwapBuffers();
}
static void gpuTreat();
#include "utils/ALClock.h"
#include "GLSobelOperator.h"


#include "WSLazySnapping.h"
#include "WSWatershed.h"

static int skin_detect(unsigned char* pix)
{
    float x0 = pix[0]/255.0;
    float x1 = pix[1]/255.0;
    float x2 = pix[2]/255.0;
    float x3 = 0.5*x0-0.4187*x1-0.0813*x2;
    float x4 = -0.1687*x0-0.3313*x1+0.5*x2;
    return (x4 <=-0.0615369 ? (x3 <=0.0678488 ? (x3 <=0.0352417 ? 0 : (x2 <=0.686631 ? 0 : 1)) : (x3 <=0.185183 ? 1 : 0)) : (x4 <=-0.029597 ? (x3 <=0.0434402 ? 0 : (x1 <=0.168271 ? 0 : 1)) : 0));
}

static void watershedTreat(GPPtr<GLBmp> bitmap)
{
    GPPtr<GLGrayBitmap> presegimg = new GLGrayBitmap(bitmap->width(), bitmap->height());
    GPPtr<GLGrayBitmap> bitmap_gray = new GLGrayBitmap(bitmap->width(), bitmap->height());
    GPPtr<GLGrayBitmap> seedImg = new GLGrayBitmap(bitmap->width(), bitmap->height());
    GLGrayBitmap::turnGray(bitmap_gray.get(), bitmap.get());
    vector<CvPoint> backPts;
    vector<CvPoint> frontpts;
    ::memset(seedImg->pixelsForWrite(), 0, seedImg->width()*seedImg->height()*sizeof(unsigned char));
    const int unit = 15;
    const int dividew = seedImg->width()/unit;
    const int divideh = seedImg->height()/unit;
    for (int i=0; i<unit; ++i)
    {
        int line = (i*divideh+divideh/2);
        auto seed_line = seedImg->pixelsForWrite() + line*seedImg->width();
        for (int j=0; j<unit; ++j)
        {
            ::memset(seed_line+j*dividew, 255, (dividew/2)*sizeof(unsigned char));
        }
    }
//    GLGrayBitmap::turnRGB(seedImg.get(), bitmap.get());
//    return;
    for (int i=0; i<bitmap->height(); ++i)
    {
        backPts.push_back(cvPoint(0, i));
        backPts.push_back(cvPoint(bitmap->width()-1, i));
    }
    for (int i=1; i<bitmap->width()-1; ++i)
    {
        backPts.push_back(cvPoint(i, 0));
        backPts.push_back(cvPoint(i, bitmap->height()-1));
    }
    GPPtr<GLGrayBitmap> bitmap_grad = new GLGrayBitmap(bitmap_gray->width(), bitmap_gray->height());
    GetGradImageNatural(bitmap_gray.get(), bitmap_grad.get(), 10.0f);
    //DoWatershedPresegmentWS(seedImg.get(), bitmap_gray.get(), presegimg.get());
    DoWatershedPresegmentWSWithGrad(seedImg.get(), bitmap_grad.get(), presegimg.get());
    for (int i=0; i<presegimg->width()*presegimg->height(); ++i)
    {
        presegimg->pixelsForWrite()[i] *=30;
    }
    
    unsigned char r_t[256];
    unsigned char g_t[256];
    unsigned char b_t[256];
    for (int i=0; i<256; ++i)
    {
        r_t[i] = (255-i)*i;
        b_t[i] = i;
        g_t[i] = 255-i;
    }
    //GLGrayBitmap::turnRGB(presegimg.get(), bitmap.get());
    GLGrayBitmap::mapRGB(presegimg.get(), bitmap.get(), r_t, g_t, b_t);
}

static void graphicutTreat(GPPtr<GLBmp> bitmap)
{
    int w = bitmap->width();
    int h = bitmap->height();
    int l = 98;//1*w/5;
    int t = 460;//(2.5)*h/5;
    int r = 736;//2*w/5;
    int b = 1322;//4*h/5;
    int temp = t;
    t = h -b;
    b = h -temp;
    GPPtr<GLGrayBitmap> bitmap_gray = new GLGrayBitmap(r-l+1, b-t+1);
    bitmap_gray->clear();
    GLGraphicCut cut(450,150.0);
    cut.initMaskRect(bitmap_gray.get());
    //cut.grabCut(bitmap.get(), bitmap_gray.get(), l, t, r, b);
    cut.grabCutCrop(bitmap.get(), bitmap_gray.get(), l, t, r, b);
    for (int i=t; i<=b; ++i)
    {
        auto mask_p = bitmap_gray->pixelsForRead() + (i-t)*bitmap_gray->width();
        auto rgb_p = (unsigned char*)(bitmap->pixels()) + i*w*4;
        for (int j=l; j<=r; ++j)
        {
            if (mask_p[j-l] > 0)
            {
                ::memset(rgb_p+j*4, 0, 4);
            }
        }
    }
    //GLGrayBitmap::turnRGB(bitmap_gray.get(), bitmap.get());
    
    //::memcpy(bitmap->pixels(), sharp_bitmap->pixels(), w*h*4*sizeof(unsigned char));
}


static void pretreat(GPPtr<GLBmp> bitmap)
{
    ALAUTOTIME;
    if (0)
    {
        gpuTreat();
        return;
    }
#if 0
    GLSobelOperator sobel(3,3);
    GLGaussOperator gauss(3);
    GLAUTOSTORAGE(kernel, int, 9);
    for (int i=0; i<9; ++i)
    {
        kernel[i] = 1;
    }
    GLTwoValueOperator two_opt(0.5);
    GPPtr<GLGrayBitmap> gray = new GLGrayBitmap(bitmap->width(), bitmap->height());
    GLGrayBitmap::turnGray(gray.get(), bitmap.get());
    GPPtr<GLGrayBitmap> gray2 = new GLGrayBitmap(bitmap->width(), bitmap->height());
    /*PingPong*/
    sobel.vFilter(gray2.get(), gray.get());
    //sobel.vFilter(gray.get(), gray2.get());
    two_opt.vFilter(gray2.get(), gray2.get());
    GLGrayBitmap::turnRGB(gray2.get(), bitmap.get());
    if (0)
    {
        GPPtr<IGLFilter> filter = new GLHistogramEqualFilter;
        filter->vFilter(bitmap.get(), bitmap.get());
    }
    if (0)
    {
        GPPtr<IGLFilter> filter = new GLSharpFilter;
        GPPtr<GLBmp> newBmp = new GLBmp(bitmap->width(), bitmap->height());
        filter->vFilter(newBmp.get(), bitmap.get());
        ::memcpy(bitmap->pixels(), newBmp->pixels(), bitmap->width()*bitmap->height()*4);
    }
#endif
    watershedTreat(bitmap);
    //graphicutTreat(bitmap);
    gTreatedTexture->upload(bitmap->pixels(), bitmap->width(), bitmap->height());
}
static void gpuTreat()
{
    //gTreatWorks = init_treat();
    //gTreatWorks = init_shallow_origin();
    //gTreatWorks = init_skin_detect();
    //gTreatWorks = init_filter_minsquare_detect();
    //gTreatWorks = init_filter();
    //gTreatWorks = init_skin_detect_treat();
    //gTreatWorks = init_skin_onepass();
    //gTreatWorks = init_skin_nolocal();
    gTreatWorks = init_guild_filter();
    gTreatedTexture->upload(NULL, gBmp->width(), gBmp->height());
    // GPCLOCK;
    float texpoints[] = {
        0.0,0.0,
        0.0,1.0,
        1.0,0.0,
        1.0,1.0
    };
    GLvboBuffer texcord(texpoints, 2, 4, GL_TRIANGLE_STRIP);
    float points[] = {
        -1.0, -1.0,
        -1.0, 1.0,
        1.0, -1.0,
        1.0, 1.0
    };
    FUNC_PRINT(gBmp->width());
    FUNC_PRINT(gBmp->height());
    ALAUTOTIME;
    {
        GLAutoFbo __fbo(*gTreatedTexture);
        GLvboBuffer temp(points, 2, 4, GL_TRIANGLE_STRIP);
        gTreatWorks->drawSingle(gTexture.get(), &temp, &texcord);
    }
}
static void init()
{
    gTexture = new GLTexture;
    gTreatedTexture = new GLTexture;
    gTexture->upload(gBmp->pixels(), gBmp->width(), gBmp->height());
    gOriginWorks = init_origin();
    pretreat(gBmp);
}
int main(int argc, char* argv[])
{
    //gBmp = new GLBmp("/Users/jiangxiaotang/Documents/shader/forge.jpg");
    //gBmp = new GLBmp("/Users/jiangxiaotang/Documents/shader/YuFamilyPhoto.jpg");
    //gBmp = new GLBmp("/Users/jiangxiaotang/Documents/shader/skintest4.jpg");
    //gBmp = new GLBmp("/Users/jiangxiaotang/Documents/shader/pic2.jpg");
    //gBmp = new GLBmp("/Users/jiangxiaotang/Data/Pictures/Pictures/7051ee7f0a4f504faaa6ca519b95d0f0.jpg");
    gBmp = new GLBmp("/Users/jiangxiaotang/Documents/shader/IMG_20150810_111131.jpg");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowPosition(50,100);
    int windoww = gBmp->width()*ENLARGE_P;
    int windowh = gBmp->height();
    const float maxw = 960.0;
    if (windoww > maxw)
    {
        float ratio = windoww/maxw;
        windoww = maxw;
        windowh = windowh/ratio;
    }
    glutInitWindowSize(windoww, windowh);
    glutCreateWindow("An Example OpenGL Program");
#ifndef __APPLE__
    glewInit();
#endif
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 1;
}

int _main(int argc, char* argv[])
{
    GPPtr<GLBmp> bitmap = new GLBmp("/Users/jiangxiaotang/Documents/shader/forge.jpg");
    GPPtr<GLGrayBitmap> mask = new GLGrayBitmap(bitmap->width(), bitmap->height());
    ::memset(mask->pixelsForWrite(), 0, bitmap->width()*bitmap->height()*sizeof(unsigned char));
    {
        GPCLOCK;
        GLGraphicCut cut(100.0,450.0);
        cut.grabCut(bitmap.get(), mask.get(), 100, 100, 200, 200);
    }
    
    return 1;
}

