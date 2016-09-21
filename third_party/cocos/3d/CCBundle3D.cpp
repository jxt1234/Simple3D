/****************************************************************************
Copyright (c) 2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "3d/CCBundle3D.h"
//#include "3d/CCObjLoader.h"

#include "base/ccMacros.h"
#include "3d/CCBundleReader.h"
#include "GL/GLProgram.h"

#define BUNDLE_TYPE_SCENE               1
#define BUNDLE_TYPE_NODE                2
#define BUNDLE_TYPE_ANIMATIONS          3
#define BUNDLE_TYPE_ANIMATION           4
#define BUNDLE_TYPE_ANIMATION_CHANNEL   5
#define BUNDLE_TYPE_MODEL               10
#define BUNDLE_TYPE_MATERIAL            16
#define BUNDLE_TYPE_EFFECT              18
#define BUNDLE_TYPE_CAMERA              32
#define BUNDLE_TYPE_LIGHT               33
#define BUNDLE_TYPE_MESH                34
#define BUNDLE_TYPE_MESHPART            35
#define BUNDLE_TYPE_MESHSKIN            36

#define CC_SAFE_DELETE(x) if (NULL!=(x)) {delete x;}

Bundle3D* Bundle3D::createBundle()
{
    auto bundle = new (std::nothrow) Bundle3D();
    return bundle;
}

void Bundle3D::destroyBundle(Bundle3D* bundle)
{
    delete bundle;
}

void Bundle3D::clear()
{
    if (NULL!=_references)
    {
        delete [] _references;
    }
}

bool Bundle3D::load(const Buffer* buffer)
{
    bool ret = false;
    _isBinary = true;
    ret = loadBinary(buffer);
    return ret;
}


bool Bundle3D::loadSkinData(const std::string& id, SkinData* skindata)
{
    skindata->resetData();

    return loadSkinDataBinary(skindata);
}

//since 3.3, to support reskin
bool Bundle3D::loadMeshDatas(MeshDatas& meshdatas)
{
    meshdatas.resetData();
    {
        if (_version == "0.1" || _version == "0.2")
        {
            return loadMeshDatasBinary_0_1(meshdatas);
        }
        else
        {
            return loadMeshDatasBinary(meshdatas);
        }
    }
    return true;
}
bool  Bundle3D::loadMeshDatasBinary(MeshDatas& meshdatas)
{
    if (!seekToFirstType(BUNDLE_TYPE_MESH))
        return false;
    unsigned int meshSize = 0;
    if (_binaryReader.read(&meshSize, 4, 1) != 1)
    {
        GPPRINT("warning: Failed to read meshdata: attribCount '%s'.", _path.c_str());
        return false;
    }
    MeshData*   meshData = nullptr;
    for(unsigned int i = 0; i < meshSize ; i++ )
    {
         unsigned int attribSize=0;
        // read mesh data
        if (_binaryReader.read(&attribSize, 4, 1) != 1 || attribSize < 1)
        {
            GPPRINT("warning: Failed to read meshdata: attribCount '%s'.", _path.c_str());
            goto FAILED;
        }
        meshData = new (std::nothrow) MeshData();
        meshData->attribCount = attribSize;
        meshData->attribs.resize(meshData->attribCount);
        for (ssize_t j = 0; j < meshData->attribCount; j++)
        {
            std::string attribute="";
            unsigned int vSize;
            if (_binaryReader.read(&vSize, 4, 1) != 1)
            {
                GPPRINT("warning: Failed to read meshdata: usage or size '%s'.", _path.c_str());
                goto FAILED;
            }
            std::string type = _binaryReader.readString();
            attribute=_binaryReader.readString();
            meshData->attribs[j].size = vSize;
            meshData->attribs[j].attribSizeBytes = meshData->attribs[j].size * 4;
            meshData->attribs[j].type =  parseGLType(type);
            meshData->attribs[j].vertexAttrib = parseGLProgramAttribute(attribute);
        }
        unsigned int vertexSizeInFloat = 0;
        // Read vertex data
        if (_binaryReader.read(&vertexSizeInFloat, 4, 1) != 1 || vertexSizeInFloat == 0)
        {
            GPPRINT("warning: Failed to read meshdata: vertexSizeInFloat '%s'.", _path.c_str());
            goto FAILED;
        }

        meshData->vertex.resize(vertexSizeInFloat);
        if (_binaryReader.read(&meshData->vertex[0], 4, vertexSizeInFloat) != vertexSizeInFloat)
        {
            GPPRINT("warning: Failed to read meshdata: vertex element '%s'.", _path.c_str());
            goto FAILED;
        }

        // Read index data
        uint32_t meshPartCount = 1;
        _binaryReader.read(&meshPartCount, 4, 1);

        for (unsigned int k = 0; k < meshPartCount; ++k)
        {
            std::vector<unsigned short>      indexArray;
            std:: string meshPartid = _binaryReader.readString();
            meshData->subMeshIds.push_back(meshPartid);
            uint32_t nIndexCount;
            if (_binaryReader.read(&nIndexCount, 4, 1) != 1)
            {
                GPPRINT("warning: Failed to read meshdata: nIndexCount '%s'.", _path.c_str());
                goto FAILED;
            }
            indexArray.resize(nIndexCount);
            if (_binaryReader.read(&indexArray[0], 2, nIndexCount) != nIndexCount)
            {
                GPPRINT("warning: Failed to read meshdata: indices '%s'.", _path.c_str());
                goto FAILED;
            }
            meshData->subMeshIndices.push_back(indexArray);
            meshData->numIndex = (int)meshData->subMeshIndices.size();
            if (_version != "0.3" && _version != "0.4" && _version != "0.5")
            {
                //read mesh aabb
                float aabb[6];
                if (_binaryReader.read(aabb, 4, 6) != 6)
                {
                    GPPRINT("warning: Failed to read meshdata: aabb '%s'.", _path.c_str());
                    goto FAILED;
                }
            }
        }
        meshdatas.meshDatas.push_back(meshData);
    }
    return true;
    
FAILED:
    {
        CC_SAFE_DELETE(meshData);
        for (auto& meshdata : meshdatas.meshDatas) {
            delete meshdata;
        }
        meshdatas.meshDatas.clear();
        return false;
    }
}
bool Bundle3D::loadMeshDatasBinary_0_1(MeshDatas& meshdatas)
{
    if (!seekToFirstType(BUNDLE_TYPE_MESH))
        return false;

    meshdatas.resetData();

    MeshData* meshdata = new (std::nothrow) MeshData();

    // read mesh data
    unsigned int attribSize=0;
    if (_binaryReader.read(&attribSize, 4, 1) != 1 || attribSize < 1)
    {
        GPPRINT("warning: Failed to read meshdata: attribCount '%s'.", _path.c_str());
        CC_SAFE_DELETE(meshdata);
        return false;
    }
    enum
    {
        VERTEX_ATTRIB_POSITION,
        VERTEX_ATTRIB_COLOR,
        VERTEX_ATTRIB_TEX_COORD,
        VERTEX_ATTRIB_NORMAL,
        VERTEX_ATTRIB_BLEND_WEIGHT,
        VERTEX_ATTRIB_BLEND_INDEX,

        VERTEX_ATTRIB_MAX,

        // backward compatibility
        VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
    };
    for (unsigned int i = 0; i < attribSize; i++)
    {
        unsigned int vUsage, vSize;
        if (_binaryReader.read(&vUsage, 4, 1) != 1 || _binaryReader.read(&vSize, 4, 1) != 1)
        {
            GPPRINT("warning: Failed to read meshdata: usage or size '%s'.", _path.c_str());
            CC_SAFE_DELETE(meshdata);
            return false;
        }

        MeshVertexAttrib meshVertexAttribute;
        meshVertexAttribute.size = vSize;
        meshVertexAttribute.attribSizeBytes = vSize * 4;
        meshVertexAttribute.type = GL_FLOAT;
        if(vUsage == VERTEX_ATTRIB_NORMAL)
        {
            vUsage= GLProgram::VERTEX_ATTRIB_NORMAL;
        }
        else if(vUsage == VERTEX_ATTRIB_BLEND_WEIGHT)
        {
            vUsage= GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT;
        }
        else if(vUsage == VERTEX_ATTRIB_BLEND_INDEX)
        {
            vUsage= GLProgram::VERTEX_ATTRIB_BLEND_INDEX;
        }
        else if(vUsage == VERTEX_ATTRIB_POSITION)
        {
            vUsage= GLProgram::VERTEX_ATTRIB_POSITION;
        }
        else if(vUsage == VERTEX_ATTRIB_TEX_COORD)
        {
            vUsage= GLProgram::VERTEX_ATTRIB_TEX_COORD;
        }
        meshVertexAttribute.vertexAttrib = vUsage;

        meshdata->attribs.push_back(meshVertexAttribute);
    }

    // Read vertex data
    if (_binaryReader.read(&meshdata->vertexSizeInFloat, 4, 1) != 1 || meshdata->vertexSizeInFloat == 0)
    {
        GPPRINT("warning: Failed to read meshdata: vertexSizeInFloat '%s'.", _path.c_str());
        CC_SAFE_DELETE(meshdata);
        return false;
    }

    meshdata->vertex.resize(meshdata->vertexSizeInFloat);
    if (_binaryReader.read(&meshdata->vertex[0], 4, meshdata->vertexSizeInFloat) != meshdata->vertexSizeInFloat)
    {
        GPPRINT("warning: Failed to read meshdata: vertex element '%s'.", _path.c_str());
        CC_SAFE_DELETE(meshdata);
        return false;
    }

    // Read index data
    unsigned int meshPartCount = 1;
    for (unsigned int i = 0; i < meshPartCount; ++i)
    {
        unsigned int nIndexCount;
        if (_binaryReader.read(&nIndexCount, 4, 1) != 1)
        {
            GPPRINT("warning: Failed to read meshdata: nIndexCount '%s'.", _path.c_str());
            CC_SAFE_DELETE(meshdata);
            return false;
        }

        std::vector<unsigned short> indices;
        indices.resize(nIndexCount);
        if (_binaryReader.read(&indices[0], 2, nIndexCount) != nIndexCount)
        {
            GPPRINT("warning: Failed to read meshdata: indices '%s'.", _path.c_str());
            CC_SAFE_DELETE(meshdata);
            return false;
        }

        meshdata->subMeshIndices.push_back(indices);
    }

    meshdatas.meshDatas.push_back(meshdata);
    return true;
}

bool Bundle3D::loadMeshDatasBinary_0_2(MeshDatas& meshdatas)
{
    if (!seekToFirstType(BUNDLE_TYPE_MESH))
        return false;

    meshdatas.resetData();

    MeshData* meshdata = new (std::nothrow) MeshData();

    // read mesh data
    unsigned int attribSize=0;
    if (_binaryReader.read(&attribSize, 4, 1) != 1 || attribSize < 1)
    {
        GPPRINT("warning: Failed to read meshdata: attribCount '%s'.", _path.c_str());
        CC_SAFE_DELETE(meshdata);
        return false;
    }
    enum
    {
        VERTEX_ATTRIB_POSITION,
        VERTEX_ATTRIB_COLOR,
        VERTEX_ATTRIB_TEX_COORD,
        VERTEX_ATTRIB_NORMAL,
        VERTEX_ATTRIB_BLEND_WEIGHT,
        VERTEX_ATTRIB_BLEND_INDEX,

        VERTEX_ATTRIB_MAX,

        // backward compatibility
        VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
    };
    for (unsigned int i = 0; i < attribSize; i++)
    {
        unsigned int vUsage, vSize;
        if (_binaryReader.read(&vUsage, 4, 1) != 1 || _binaryReader.read(&vSize, 4, 1) != 1)
        {
            GPPRINT("warning: Failed to read meshdata: usage or size '%s'.", _path.c_str());
            CC_SAFE_DELETE(meshdata);
            return false;
        }

        MeshVertexAttrib meshVertexAttribute;
        meshVertexAttribute.size = vSize;
        meshVertexAttribute.attribSizeBytes = vSize * 4;
        meshVertexAttribute.type = GL_FLOAT;
        if(vUsage == VERTEX_ATTRIB_NORMAL)
        {
            vUsage= GLProgram::VERTEX_ATTRIB_NORMAL;
        }
        else if(vUsage == VERTEX_ATTRIB_BLEND_WEIGHT)
        {
            vUsage= GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT;
        }
        else if(vUsage == VERTEX_ATTRIB_BLEND_INDEX)
        {
            vUsage= GLProgram::VERTEX_ATTRIB_BLEND_INDEX;
        }
        else if(vUsage == VERTEX_ATTRIB_POSITION)
        {
            vUsage= GLProgram::VERTEX_ATTRIB_POSITION;
        }
        else if(vUsage == VERTEX_ATTRIB_TEX_COORD)
        {
            vUsage= GLProgram::VERTEX_ATTRIB_TEX_COORD;
        }
        meshVertexAttribute.vertexAttrib = vUsage;

        meshdata->attribs.push_back(meshVertexAttribute);
    }

    // Read vertex data
    if (_binaryReader.read(&meshdata->vertexSizeInFloat, 4, 1) != 1 || meshdata->vertexSizeInFloat == 0)
    {
        GPPRINT("warning: Failed to read meshdata: vertexSizeInFloat '%s'.", _path.c_str());
        CC_SAFE_DELETE(meshdata);
        return false;
    }

    meshdata->vertex.resize(meshdata->vertexSizeInFloat);
    if (_binaryReader.read(&meshdata->vertex[0], 4, meshdata->vertexSizeInFloat) != meshdata->vertexSizeInFloat)
    {
        GPPRINT("warning: Failed to read meshdata: vertex element '%s'.", _path.c_str());
        CC_SAFE_DELETE(meshdata);
        return false;
    }

    // read submesh
    unsigned int submeshCount;
    if (_binaryReader.read(&submeshCount, 4, 1) != 1)
    {
        GPPRINT("warning: Failed to read meshdata: submeshCount '%s'.", _path.c_str());
        CC_SAFE_DELETE(meshdata);
        return false;
    }

    for (unsigned int i = 0; i < submeshCount; ++i)
    {
        unsigned int nIndexCount;
        if (_binaryReader.read(&nIndexCount, 4, 1) != 1)
        {
            GPPRINT("warning: Failed to read meshdata: nIndexCount '%s'.", _path.c_str());
            CC_SAFE_DELETE(meshdata);
            return false;
        }

        std::vector<unsigned short> indices;
        indices.resize(nIndexCount);
        if (_binaryReader.read(&indices[0], 2, nIndexCount) != nIndexCount)
        {
            GPPRINT("warning: Failed to read meshdata: indices '%s'.", _path.c_str());
            CC_SAFE_DELETE(meshdata);
            return false;
        }

        meshdata->subMeshIndices.push_back(indices);
    }

    meshdatas.meshDatas.push_back(meshdata);
    
    return true;
}

bool Bundle3D::loadNodes(NodeDatas& nodedatas)
{
    if (_version == "0.1" || _version == "1.2" || _version == "0.2")
    {
        SkinData   skinData;
        if (!loadSkinData("", &skinData))
        {
            auto node= new (std::nothrow) NodeData();
            auto modelnode = new (std::nothrow) ModelData();
            modelnode->matrialId = "";
            modelnode->subMeshId = "";
            node->modelNodeDatas.push_back(modelnode);
            nodedatas.nodes.push_back(node);
            return true;
        }
        
        auto nodeDatas = new (std::nothrow) NodeData*[skinData.skinBoneNames.size() + skinData.nodeBoneNames.size()];
        int index = 0;
        size_t i;
        for (i = 0; i < skinData.skinBoneNames.size(); i++)
        {
            nodeDatas[index] = new (std::nothrow) NodeData();
            nodeDatas[index]->id = skinData.skinBoneNames[i];
            nodeDatas[index]->transform = skinData.skinBoneOriginMatrices[i];
            index++;
        }
        for (i = 0; i < skinData.nodeBoneNames.size(); i++)
        {
            nodeDatas[index] = new (std::nothrow) NodeData();
            nodeDatas[index]->id = skinData.nodeBoneNames[i];
            nodeDatas[index]->transform = skinData.nodeBoneOriginMatrices[i];
            index++;
        }
        for (const auto& it : skinData.boneChild)
        {
            const auto& children = it.second;
            auto parent = nodeDatas[it.first];
            for (const auto& child : children)
            {
                parent->children.push_back(nodeDatas[child]);
            }
        }
        nodedatas.skeleton.push_back(nodeDatas[skinData.rootBoneIndex]);
        auto node= new (std::nothrow) NodeData();
        auto modelnode = new (std::nothrow) ModelData();
        modelnode->matrialId = "";
        modelnode->subMeshId = "";
        modelnode->bones = skinData.skinBoneNames;
        modelnode->invBindPose = skinData.inverseBindPoseMatrices;
        node->modelNodeDatas.push_back(modelnode);
        nodedatas.nodes.push_back(node);
        delete[] nodeDatas;
    }
    else
    {
        loadNodesBinary(nodedatas);
    }
    return true;
}
bool Bundle3D::loadMaterials(MaterialDatas& materialdatas)
{
    materialdatas.resetData();
    {
        if (_version == "0.1")
        {
            return loadMaterialsBinary_0_1(materialdatas);
        }
        else if (_version == "0.2")
        {
            return loadMaterialsBinary_0_2(materialdatas);
        }
        else
        {
            return loadMaterialsBinary(materialdatas);
        } 
    }
    return true;
}
bool Bundle3D::loadMaterialsBinary(MaterialDatas& materialdatas)
{
    if (!seekToFirstType(BUNDLE_TYPE_MATERIAL))
        return false;
    unsigned int materialnum = 1;
    _binaryReader.read(&materialnum, 4, 1);
    for (unsigned int i = 0; i < materialnum; i++)
    {
        NMaterialData materialData;
        materialData.id = _binaryReader.readString();
        
        // skip: diffuse(3), ambient(3), emissive(3), opacity(1), specular(3), shininess(1)
        float  data[14];
        _binaryReader.read(&data,sizeof(float), 14);
        
        unsigned int textureNum = 1;
        _binaryReader.read(&textureNum, 4, 1);
        for (unsigned int j = 0; j < textureNum; j++)
        {
            NTextureData  textureData;
            textureData.id = _binaryReader.readString();
            if (textureData.id.empty())
            {
                GPPRINT("warning: Failed to read Materialdata: texturePath is empty '%s'.", textureData.id.c_str());
                return false;
            }
            std::string texturePath = _binaryReader.readString();
            if (texturePath.empty())
            {
                GPPRINT("warning: Failed to read Materialdata: texturePath is empty '%s'.", _path.c_str());
                return false;
            }

            textureData.filename = texturePath.empty() ? texturePath : _modelPath + texturePath;
            float  uvdata[4];
            _binaryReader.read(&uvdata,sizeof(float), 4);
            textureData.type  = parseGLTextureType(_binaryReader.readString());
            textureData.wrapS= parseGLType(_binaryReader.readString());
            textureData.wrapT= parseGLType(_binaryReader.readString());
            materialData.textures.push_back(textureData);
        }
        materialdatas.materials.push_back(materialData);
    }
    return true;
}
bool Bundle3D::loadMaterialsBinary_0_1(MaterialDatas& materialdatas)
{
    if (!seekToFirstType(BUNDLE_TYPE_MATERIAL))
        return false;

    NMaterialData materialData;

    std::string texturePath = _binaryReader.readString();
    if (texturePath.empty())
    {
        GPPRINT("warning: Failed to read Materialdata: texturePath is empty '%s'.", _path.c_str());
        return false;
    }

    NTextureData textureData;
    textureData.filename = texturePath.empty() ? texturePath : _modelPath + texturePath;
    textureData.type= NTextureData::Usage::Diffuse;
    textureData.id="";
    materialData.textures.push_back(textureData);
    materialdatas.materials.push_back(materialData);
    return true;
}

bool Bundle3D::loadMaterialsBinary_0_2(MaterialDatas& materialdatas)
{
    if (!seekToFirstType(BUNDLE_TYPE_MATERIAL))
        return false;

    unsigned int materialnum = 1;
    _binaryReader.read(&materialnum, 4, 1);

    for (unsigned int i = 0; i < materialnum; i++)
    {
        NMaterialData materialData;

        std::string texturePath = _binaryReader.readString();
        if (texturePath.empty())
        {
            GPPRINT("warning: Failed to read Materialdata: texturePath is empty '%s'.", _path.c_str());
            return true;
        }

        NTextureData textureData;
        textureData.filename = texturePath.empty() ? texturePath : _modelPath + texturePath;
        textureData.type= NTextureData::Usage::Diffuse;
        textureData.id="";
        materialData.textures.push_back(textureData);
        materialdatas.materials.push_back(materialData);
    }
    return true;
}

bool Bundle3D::loadBinary(const Buffer* buffer)
{
    clear();
    std::string path = "NULL";
    
    // Initialise bundle reader
    _binaryReader.init(buffer->get(),  buffer->size());
    
    // Read identifier info
    char identifier[] = { 'C', '3', 'B', '\0'};
    char sig[4];
    if (_binaryReader.read(sig, 1, 4) != 4 || memcmp(sig, identifier, 4) != 0)
    {
        clear();
        GPPRINT("warning: Invalid identifier: %s", path.c_str());
        return false;
    }
    
    // Read version
    unsigned char ver[2];
    if (_binaryReader.read(ver, 1, 2)!= 2){
        GPPRINT("warning: Failed to read version:");
        return false;
    }
    
    char version[20] = {0};
    sprintf(version, "%d.%d", ver[0], ver[1]);
    _version = version;
    
    // Read ref table size
    if (_binaryReader.read(&_referenceCount, 4, 1) != 1)
    {
        clear();
        GPPRINT("warning: Failed to read ref table size '%s'.", path.c_str());
        return false;
    }
    
    // Read all refs
    if (NULL != _references)
    {
        delete [] _references;
        _references = NULL;
    }
    _references = new (std::nothrow) Reference[_referenceCount];
    for (unsigned int i = 0; i < _referenceCount; ++i)
    {
        if ((_references[i].id = _binaryReader.readString()).empty() ||
            _binaryReader.read(&_references[i].type, 4, 1) != 1 ||
            _binaryReader.read(&_references[i].offset, 4, 1) != 1)
        {
            clear();
            GPPRINT("warning: Failed to read ref number %u for bundle '%s'.", i, path.c_str());
            if (NULL != _references)
            {
                delete [] _references;
                _references = NULL;
            }
            return false;
        }
    }
    
    return true;
}



bool Bundle3D::loadSkinDataBinary(SkinData* skindata)
{
    if (!seekToFirstType(BUNDLE_TYPE_MESHSKIN))
        return false;
    
    std::string boneName = _binaryReader.readString();
    
    // transform
    float bindShape[16];
    if (!_binaryReader.readMatrix(bindShape))
    {
        GPPRINT("warning: Failed to read SkinData: bindShape matrix  '%s'.", _path.c_str());
        return false;
    }
    
    // bone count
    unsigned int boneNum;
    if (!_binaryReader.read(&boneNum))
    {
        GPPRINT("warning: Failed to read SkinData: boneNum  '%s'.", _path.c_str());
        return false;
    }
    
    // Fix bug: check if the bone number is 0.
    if (boneNum == 0)
        return false;
    
    // bone names and bind pos
    float bindpos[16];
    for (unsigned int i = 0; i < boneNum; i++)
    {
        std::string skinBoneName = _binaryReader.readString();
        skindata->skinBoneNames.push_back(skinBoneName);
        if (!_binaryReader.readMatrix(bindpos))
        {
            GPPRINT("warning: Failed to load SkinData: bindpos '%s'.", _path.c_str());
            return false;
        }
        GLMatrix4 matrix(bindpos);
        skindata->inverseBindPoseMatrices.push_back(matrix);
    }
    
    skindata->skinBoneOriginMatrices.resize(boneNum);
    
    boneName = _binaryReader.readString();
    
    // bind shape
    _binaryReader.readMatrix(bindShape);
    int rootIndex = skindata->getSkinBoneNameIndex(boneName);
    if(rootIndex < 0)
    {
        skindata->addNodeBoneNames(boneName);
        rootIndex = skindata->getBoneNameIndex(boneName);
        skindata->nodeBoneOriginMatrices.push_back(bindShape);
    }
    else
    {
        skindata->skinBoneOriginMatrices[rootIndex] = bindShape;
    }
    
    // set root bone index
    skindata->rootBoneIndex = rootIndex;
    
    // read parent and child relationship map
    float transform[16];
    unsigned int linkNum;
    _binaryReader.read(&linkNum);
    for (unsigned int i = 0; i < linkNum; ++i)
    {
        std::string id = _binaryReader.readString();
        int index = skindata->getSkinBoneNameIndex(id);
        
        
        std::string parentid = _binaryReader.readString();
        
        if (!_binaryReader.readMatrix(transform))
        {
            GPPRINT("warning: Failed to load SkinData: transform '%s'.", _path.c_str());
            return false;
        }
        
        if(index < 0)
        {
            skindata->addNodeBoneNames(id);
            index = skindata->getBoneNameIndex(id);
            skindata->nodeBoneOriginMatrices.push_back(transform);
        }
        else
        {
            skindata->skinBoneOriginMatrices[index] = transform;
        }
        
        int parentIndex = skindata->getSkinBoneNameIndex(parentid);
        if(parentIndex < 0)
        {
            skindata->addNodeBoneNames(parentid);
            parentIndex = skindata->getBoneNameIndex(parentid);
        }
        
        skindata->boneChild[parentIndex].push_back(index);
        
    }
    
    return true;
}


bool Bundle3D::loadNodesBinary(NodeDatas& nodedatas)
{
    if (!seekToFirstType(BUNDLE_TYPE_NODE))
        return false;

    unsigned int nodeSize = 0;
    if (_binaryReader.read(&nodeSize, 4, 1) != 1)
    {
        GPPRINT("warning: Failed to read nodes");
        return false;
    }

    // traverse the nodes again
    for (int i = 0; i < nodeSize; i++)
    {
        bool skeleton = false;
        NodeData* nodedata = parseNodesRecursivelyBinary(skeleton, nodeSize == 1);

        if (skeleton)
            nodedatas.skeleton.push_back(nodedata);
        else
            nodedatas.nodes.push_back(nodedata);
    }
    return true;
}
NodeData* Bundle3D::parseNodesRecursivelyBinary(bool& skeleton, bool singleSprite)
{
    // id
    std::string id = _binaryReader.readString();
    // is skeleton
    bool skeleton_;
    if (_binaryReader.read(&skeleton_, 1, 1) != 1)
    {
        GPPRINT("warning: Failed to read is skeleton");
        return nullptr;
    }
    if (skeleton_)
        skeleton = true;
    
    // transform
    Mat4 transform;
    if (!_binaryReader.readMatrix(transform.get()))
    {
        GPPRINT("warning: Failed to read transform matrix");
        return nullptr;
    }
    // parts
    unsigned int partsSize = 0;
    if (_binaryReader.read(&partsSize, 4, 1) != 1)
    {
        GPPRINT("warning: Failed to read meshdata: attribCount '%s'.", _path.c_str());
        return nullptr;
    }

    NodeData* nodedata = new (std::nothrow) NodeData();
    nodedata->id = id;
    
    bool isSkin = false;
    
    if (partsSize > 0)
    {
        for (unsigned int i = 0; i < partsSize; i++)
        {
            auto modelnodedata  = new (std::nothrow) ModelData();
            modelnodedata->subMeshId = _binaryReader.readString();
            modelnodedata->matrialId = _binaryReader.readString();

            if (modelnodedata->subMeshId == "" || modelnodedata->matrialId == "")
            {
                std::string err = "Node " + nodedata->id + " part is missing meshPartId or materialId";
                GPPRINT("Node %s part is missing meshPartId or materialId", nodedata->id.c_str());
                CC_SAFE_DELETE(modelnodedata);
                CC_SAFE_DELETE(nodedata);
                return nullptr;
            }

            // read bone
            unsigned int bonesSize = 0;
            if (_binaryReader.read(&bonesSize, 4, 1) != 1)
            {
                GPPRINT("warning: Failed to read meshdata: attribCount '%s'.", _path.c_str());
                CC_SAFE_DELETE(modelnodedata);
                CC_SAFE_DELETE(nodedata);
                return nullptr;
            }

            if (bonesSize > 0)
            {
                for (unsigned int j = 0; j < bonesSize; j++)
                {
                    std::string name = _binaryReader.readString();
                    modelnodedata->bones.push_back(name);

                    Mat4 invbindpos;
                    if (!_binaryReader.readMatrix(invbindpos.get()))
                    {
                        CC_SAFE_DELETE(modelnodedata);
                        CC_SAFE_DELETE(nodedata);
                        return nullptr;
                    }

                    modelnodedata->invBindPose.push_back(invbindpos);
                }
                isSkin = true;
            }
            unsigned int uvMapping = 0;
            if (_binaryReader.read(&uvMapping, 4, 1) != 1)
            {
                GPPRINT("warning: Failed to read nodedata: uvMapping '%s'.", _path.c_str());
                CC_SAFE_DELETE(modelnodedata);
                CC_SAFE_DELETE(nodedata);
                return nullptr;
            }
            for(unsigned int j = 0; j < uvMapping; j++)
            {
                unsigned int textureIndexSize=0;
                if (_binaryReader.read(&textureIndexSize, 4, 1) != 1)
                {
                    GPPRINT("warning: Failed to read meshdata: attribCount '%s'.", _path.c_str());
                    CC_SAFE_DELETE(modelnodedata);
                    CC_SAFE_DELETE(nodedata);
                    return nullptr;
                }
                for(unsigned int k = 0; k < textureIndexSize; k++)
                {
                    unsigned int index=0;
                    if (_binaryReader.read(&index, 4, 1) != 1)
                    {
                        CC_SAFE_DELETE(modelnodedata);
                        CC_SAFE_DELETE(nodedata);
                        return nullptr;
                    }
                }
            }
            nodedata->modelNodeDatas.push_back(modelnodedata);
        }
    }

    // set transform
   if(_version == "0.1" || _version == "0.2" || _version == "0.3" || _version == "0.4" || _version == "0.5" || _version == "0.6")
   {
       if(isSkin || singleSprite)
       {
           nodedata->transform.reset();
       }
       else
       {
           nodedata->transform = transform;
       }
   }
   else
   {
       nodedata->transform = transform;
   }
    
    unsigned int childrenSize = 0;
    if (_binaryReader.read(&childrenSize, 4, 1) != 1)
    {
        GPPRINT("warning: Failed to read meshdata: attribCount '%s'.", _path.c_str());
        CC_SAFE_DELETE(nodedata);
        return nullptr;
    }
    if (childrenSize > 0)
    {
        for (unsigned int i = 0; i <  childrenSize; i++)
        {
            NodeData* tempdata = parseNodesRecursivelyBinary(skeleton, singleSprite);
            nodedata->children.push_back(tempdata);
        }
    }
    return nodedata;
}

GLenum Bundle3D::parseGLType(const std::string& str)
{
    if (str == "GL_BYTE")
    {
        return GL_BYTE;
    }
    else if(str == "GL_UNSIGNED_BYTE")
    {
        return GL_UNSIGNED_BYTE;
    }
    else if(str == "GL_SHORT")
    {
        return GL_SHORT;
    }
    else if(str == "GL_UNSIGNED_SHORT")
    {
        return GL_UNSIGNED_SHORT;
    }
    else if(str == "GL_INT")
    {
        return GL_INT;
    }
    else if (str == "GL_UNSIGNED_INT")
    {
        return GL_UNSIGNED_INT;
    }
    else if (str == "GL_FLOAT")
    {
        return GL_FLOAT;
    }
    else if (str == "REPEAT")
    {
        return GL_REPEAT;
    }
    else if (str == "CLAMP")
    {
        return GL_CLAMP_TO_EDGE;
    }
    else
    {
        CCASSERT(false, "Invalid GL type");
        return 0;
    }
}
NTextureData::Usage Bundle3D::parseGLTextureType(const std::string& str)
{
    if (str == "AMBIENT")
    {
        return NTextureData::Usage::Ambient;
    }
    else if(str == "BUMP")
    {
        return NTextureData::Usage::Bump;
    }
    else if(str == "DIFFUSE")
    {
        return NTextureData::Usage::Diffuse;
    }
    else if(str == "EMISSIVE")
    {
        return NTextureData::Usage::Emissive;
    }
    else if(str == "NONE")
    {
        return NTextureData::Usage::None;
    }
    else if (str == "NORMAL")
    {
        return NTextureData::Usage::Normal;
    }
    else if (str == "REFLECTION")
    {
        return NTextureData::Usage::Reflection;
    }
    else if (str == "SHININESS")
    {
        return NTextureData::Usage::Shininess;
    }
    else if (str == "SPECULAR")
    {
        return NTextureData::Usage::Specular;
    }
    else if (str == "TRANSPARENCY")
    {
        return NTextureData::Usage::Transparency;
    }
    else
    {
        CCASSERT(false, "Wrong Texture type");
        return NTextureData::Usage::Unknown;
    }
}
unsigned int Bundle3D::parseGLProgramAttribute(const std::string& str)
{
    if (str == "VERTEX_ATTRIB_POSITION")
    {
        return GLProgram::VERTEX_ATTRIB_POSITION;
    }
    else if (str == "VERTEX_ATTRIB_COLOR")
    {
        return GLProgram::VERTEX_ATTRIB_COLOR;
    }
    else if (str == "VERTEX_ATTRIB_TEX_COORD")
    {
        return GLProgram::VERTEX_ATTRIB_TEX_COORD;
    }
    else if (str == "VERTEX_ATTRIB_TEX_COORD1")
    {
        return GLProgram::VERTEX_ATTRIB_TEX_COORD1;
    }
    else if (str == "VERTEX_ATTRIB_TEX_COORD2")
    {
        return GLProgram::VERTEX_ATTRIB_TEX_COORD2;
    }
    else if (str == "VERTEX_ATTRIB_TEX_COORD3")
    {
        return GLProgram::VERTEX_ATTRIB_TEX_COORD3;
    }
    //comment out them
//    else if (str == "VERTEX_ATTRIB_TEX_COORD4")
//    {
//        return GLProgram::VERTEX_ATTRIB_TEX_COORD4;
//    }
//    else if (str == "VERTEX_ATTRIB_TEX_COORD5")
//    {
//        return GLProgram::VERTEX_ATTRIB_TEX_COORD5;
//    }
//    else if (str == "VERTEX_ATTRIB_TEX_COORD6")
//    {
//        return GLProgram::VERTEX_ATTRIB_TEX_COORD6;
//    }
//    else if (str == "VERTEX_ATTRIB_TEX_COORD7")
//    {
//        return GLProgram::VERTEX_ATTRIB_TEX_COORD7;
//    }
    else if (str == "VERTEX_ATTRIB_NORMAL")
    {
        return GLProgram::VERTEX_ATTRIB_NORMAL;
    }
    else if (str == "VERTEX_ATTRIB_BLEND_WEIGHT")
    {
        return GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT;
    }
    else if (str == "VERTEX_ATTRIB_BLEND_INDEX")
    {
        return GLProgram::VERTEX_ATTRIB_BLEND_INDEX;
    }
    else if (str == "VERTEX_ATTRIB_TANGENT")
    {
        return GLProgram::VERTEX_ATTRIB_TANGENT;
    }
    else if (str == "VERTEX_ATTRIB_BINORMAL")
    {
        return GLProgram::VERTEX_ATTRIB_BINORMAL;
    }
    else
    {
        CCASSERT(false, "Wrong Attribute type");
        return -1;
    }
}

void Bundle3D::getModelRelativePath(const std::string& path)
{
    ssize_t index = path.find_last_of('/');
    std::string fullModelPath;
    _modelPath = path.substr(0, index + 1);
}

Reference* Bundle3D::seekToFirstType(unsigned int type, const std::string& id)
{
    // for each Reference
    for (unsigned int i = 0; i < _referenceCount; ++i)
    {
        Reference* ref = &_references[i];
        if (ref->type == type)
        {
            // if id is not a null string, we also need to check the Reference's id.
            if (id != "" && id != ref->id)
            {
                continue;
            }
            
            // Found a match
            if (_binaryReader.seek(ref->offset, SEEK_SET) == false)
            {
                GPPRINT("warning: Failed to seek to object '%s' in bundle '%s'.", ref->id.c_str(), _path.c_str());
                return nullptr;
            }
            return ref;
        }
    }
    return nullptr;
}



Bundle3D::Bundle3D()
: _modelPath(""),
_path(""),
_version(""),
_referenceCount(0),
_references(nullptr),
_isBinary(false)
{
}
Bundle3D::~Bundle3D()
{
    clear();

}
