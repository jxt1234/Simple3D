#include "core/GLBmp.h"
#include "utils/debug.h"
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
    GLASSERT(argc>=4);
    const char* rgbfile = argv[1];
    const char* blackfile = argv[2];
    const char* outputfile = argv[3];
    GLBmp rgb;
    GLBmp black;
    rgb.loadPicture(rgbfile);
    black.loadPicture(blackfile);
    GLASSERT(rgb.getWidth() == black.getWidth());
    GLASSERT(rgb.getHeight() == black.getHeight());
    auto w = rgb.getWidth();
    auto h = rgb.getHeight();
    unsigned char* rgb_p = (unsigned char*)rgb.pixels();
    unsigned char* black_p = (unsigned char*)black.pixels();
    ofstream output(outputfile);
    GLASSERT(!output.fail());
    for (auto i=0; i<w; ++i)
    {
        for (auto j=0; j<h; ++j)
        {
            int bl = black_p[1] <100 ? 0 : 1;
            output << bl << " "<<(float)rgb_p[0] <<" "<< (float)rgb_p[1] <<" "<< (float)rgb_p[2] << endl;
            //output << bl << " "<<(float)rgb_p[0] <<" "<< (float)rgb_p[1] <<" "<< (float)rgb_p[2] << " "<< (float)rgb_p[3] << endl;
            rgb_p+=4;
            black_p+=4;
        }
    }
    return 1;
}
