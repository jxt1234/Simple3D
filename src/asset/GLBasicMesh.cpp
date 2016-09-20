#include "asset/GLBasicMesh.h"

GLBasicMesh* GLBasicMesh::load(std::istream& input)
{
    uint32_t pointNumber;
    input.read((char*)&pointNumber, sizeof(uint32_t));
    
    GLBasicMesh* mesh = new GLBasicMesh(pointNumber);
    input.read((char*)mesh->get(), pointNumber*sizeof(Point));
    return mesh;
}

void GLBasicMesh::dump(std::ostream& output) const
{
    output.write((char*)&mPointNumber, sizeof(uint32_t));
    output.write((char*)mPoints, sizeof(Point)*mPointNumber);
}
