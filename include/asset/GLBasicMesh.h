#ifndef ASSET_GLBASICMESH_H
#define ASSET_GLBASICMESH_H
#include <istream>
#include <ostream>
class GLBasicMesh
{
public:
    struct Point
    {
        double vertex[4];
        double normal[3];
        double tangent[4];
        double color[4];
        double uv[2];
    };
    GLBasicMesh(uint32_t n)
    {
        mPointNumber = n;
        mPoints = new Point[n];
    }
    
    ~ GLBasicMesh()
    {
        delete [] mPoints;
    }
    
    Point* get() const {return mPoints;}
    uint32_t size() const {return mPointNumber;}
    
    static GLBasicMesh* load(std::istream& input);
    
    void dump(std::ostream& output) const;

private:
    Point* mPoints;
    uint32_t mPointNumber;
};
#endif
