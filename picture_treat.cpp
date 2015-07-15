#include "core/GLBmp.h"
#include "utils/debug.h"
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "GL/GLContext.h"
#include "GL/GLAutoFbo.h"
#include "GL/GLBitmapWork.h"
#include "GL/GLFilterWork.h"
#include "GL/GLMultiPassDrawWork.h"
#include "GL/GLDrawWork.h"
#define ENLARGE_P 1.0

using namespace std;
static string loadFiles(const char* name)
{
    ifstream vertex(name);
    GLASSERT(!vertex.fail());
    ostringstream vertex_s;
    vertex_s << vertex.rdbuf();
    return vertex_s.str();
}

static IGLDrawWork* init_skin_detect_treat(int w, int h)
{
    const char* vertex = "/Users/jiangxiaotang/Documents/shader/ShallowOnePass.vex";
    const char* frag = "/Users/jiangxiaotang/Documents/shader/skin_with_lsd.fra";

    map<string, float> firstunifom;
    firstunifom["texelWidth"] = 1.0/w;
    firstunifom["texelHeight"] = 0.0;
    firstunifom["filterRatio"] = 1.0;
    firstunifom["sigma_c"] = 30.0;
    firstunifom["sigma_s"] = 0.1;

    map<string, float> secondunifom;
    secondunifom["texelWidth"] = 0.0;
    secondunifom["texelHeight"] = 1.0/h;
    secondunifom["filterRatio"] = 1.0;
    secondunifom["sigma_c"] = 30.0;
    secondunifom["sigma_s"] = 0.1;

    vector<GPPtr<IGLDrawWork> > works;
    works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &secondunifom));
    works.push_back(new GLDrawWork(loadFiles(vertex), loadFiles(frag), &firstunifom));

    return new GLMultiPassDrawWork(works);
}

GPPtr<GLBmp> pretreat(GPPtr<GLBmp> src)
{
    GPPtr<IGLDrawWork> work = init_skin_detect_treat(src->width(), src->height());
    GPPtr<GLBmp> dst = new GLBmp(src->width(), src->height());
    GPPtr<GLTexture> srct = new GLTexture;
    GPPtr<GLTexture> dstt = new GLTexture;
    srct->upload(src->pixels(), src->width(), src->height());
    dstt->upload(NULL, src->width(), src->height());
    {
        GLAutoFbo __fbo(*dstt);
        float texpoints[] = {
            0.0,0.0,
            0.0,1.0,
            1.0,0.0,
            1.0,1.0
        };
        GLvboBuffer texcord(texpoints, 2, 4, GL_TRIANGLE_STRIP);
        /*Treated picture*/
        float points[] = {
            -1.0, -1.0,
            -1.0, 1.0,
            1.0, -1.0,
            1.0, 1.0
        };
        GLvboBuffer temp(points, 2, 4, GL_TRIANGLE_STRIP);
        auto tex = srct.get();
        work->onDraw(&tex, 1, &temp, &texcord);
        dstt->download(dst->pixels());
    }
    return dst;
}

int main(int argc, char* argv[])
{
    GLASSERT(argc>=4);
    GLContext::init();
    const char* inputfile = argv[1];
    const char* outputfile = argv[2];
    const char* method = argv[3];//TODO
    GPPtr<GLBmp> rgb_origin = new GLBmp(inputfile);
    GPPtr<GLBmp> rgb = pretreat(rgb_origin);
    rgb->save(outputfile);
    GLContext::destroy();
    return 1;
}
