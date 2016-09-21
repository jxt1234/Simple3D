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

#ifndef __CCBUNDLE3D_H__
#define __CCBUNDLE3D_H__

#include "3d/CCBundle3DData.h"
#include "3d/CCBundleReader.h"

/**
 * @addtogroup _3d
 * @{
 */

class Animation3D;

/**
 * @brief Defines a bundle file that contains a collection of assets. Mesh, Material, MeshSkin, Animation
 * There are two types of bundle files, c3t and c3b.
 * c3t text file
 * c3b binary file
 * @js NA
 * @lua NA
 */
class Bundle3D
{
public:
    class Buffer : public GPRefCount
    {
    public:
        Buffer(size_t length)
        {
            mLength = length;
            mBuffer = new char[length];
            mOwn = true;
        }
        Buffer(const char* data, size_t length)
        {
            mBuffer = (char*)data;
            mLength = length;
            mOwn = false;
        }
        ~ Buffer()
        {
            if (mOwn)
            {
                delete [] mBuffer;
            }
        }
        
        char* get() const {return mBuffer;}
        size_t size() const {return mLength;}
    private:
        char* mBuffer;
        size_t mLength;
        bool mOwn;
    };
    /**
     * create a new bundle, destroy it when finish using it
     */
    static Bundle3D* createBundle();
    
    static void destroyBundle(Bundle3D* bundle);
    
	virtual void clear();

    /**
     * load a file. You must load a file first, then call loadMeshData, loadSkinData, and so on
     * @param path File to be loaded
     * @return result of load
     */
    virtual bool load(const Buffer* buffer);
    
    /**
     * load skin data from bundle
     * @param id The ID of the skin, load the first Skin in the bundle if it is empty
     */
    virtual bool loadSkinData(const std::string& id, SkinData* skindata);
    
    /**
     * load material data from bundle
     * @param id The ID of the animation, load the first animation in the bundle if it is empty
     */
    
    //since 3.3, to support reskin
    virtual bool loadMeshDatas(MeshDatas& meshdatas);
    //since 3.3, to support reskin
    virtual bool loadNodes(NodeDatas& nodedatas);
    //since 3.3, to support reskin
    virtual bool loadMaterials(MaterialDatas& materialdatas);
    
  
protected:

    bool loadBinary(const Buffer* buffer);
    bool loadMeshDatasBinary(MeshDatas& meshdatas);
    bool loadMeshDatasBinary_0_1(MeshDatas& meshdatas);
    bool loadMeshDatasBinary_0_2(MeshDatas& meshdatas);
    bool loadMaterialsBinary(MaterialDatas& materialdatas);
    bool loadMaterialsBinary_0_1(MaterialDatas& materialdatas);
    bool loadMaterialsBinary_0_2(MaterialDatas& materialdatas);
    bool loadSkinDataBinary(SkinData* skindata);

    /**
     * load nodes of binary
     */
    bool loadNodesBinary(NodeDatas& nodedatas);
    NodeData* parseNodesRecursivelyBinary(bool& skeleton, bool singleSprite);

    /**
     * get define data type
     * @param str The type in string
     */
    GLenum parseGLType(const std::string& str);

     /**
     * get define data type
     * @param str The type in string
     */
    NTextureData::Usage parseGLTextureType(const std::string& str);

    /**
     * get vertex attribute type
     * @param str The type in string
     */
    unsigned int parseGLProgramAttribute(const std::string& str);

    /*
     * get model path
     * @param str Full path of model file
     */
    void getModelRelativePath(const std::string& path);

    /*
     * set the read position in buffer to the target type
     * @param The data type
     * @param The data id
     */
    Reference* seekToFirstType(unsigned int type, const std::string& id = "");

    Bundle3D();
    virtual ~Bundle3D();
    
protected:
    std::string _modelPath;
    std::string _path = "NULL";
    std::string _version;// the c3b or c3t version
    

    // for binary reading
    BundleReader _binaryReader;
    unsigned int _referenceCount;
    Reference* _references;
    bool  _isBinary;
};

// end of 3d group
/// @}


#endif // __CCBUNDLE3D_H__
