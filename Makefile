all:libglsl.so test.out gputest.out example.out convert_data.out picture_treat.out gp_color_table_data_make.out color_extract.out picture_scale.out 

ALL_INCLUESlibglsl.so= include//AllShader.h include//asset/GLBasicMesh.h include//asset/GLIAsset.h include//asset/GLLightObjAsset.h include//core/GLBitmapFactory.h include//core/GLBmp.h include//core/GLDepthBuffer.h include//core/GLDynamicBitmap.h include//core/GLGrayBitmap.h include//core/GLRasterization.h include//core/GLRect.h include//fragment/GL_FragColor.h include//fragment/GL_FragPosition.h include//fragment/GL_FragTexcord.h include//fragment/GL_vPosition.h include//fragment/GLAbstractRasterizatedVarying.h include//fragment/GLLightFunction.h include//fragment/GLTexture2D.h include//fragment/GLWritePixels.h include//GL/debug.h include//GL/GLAutoFbo.h include//GL/GLAutoProgram.h include//GL/GLBasic3DObject.h include//GL/GLBezier.h include//GL/GLBiCubicCurveObj.h include//GL/GLBicubicWork.h include//GL/GLBitmapWork.h include//GL/GLBitmapWorkFactory.h include//GL/GLCamera.h include//GL/GLContext.h include//GL/GLCurveObject.h include//GL/GLCurveObjectFactory.h include//GL/GLDrawWork.h include//GL/GLFilterWork.h include//GL/GLFixScaleDrawWork.h include//GL/GLLightCurveObj.h include//GL/GLLightScene.h include//GL/GLMixWork.h include//GL/GLMultiBitmapWork.h include//GL/GLMultiPassDrawWork.h include//GL/GLMultiPassWork.h include//GL/GLObject.h include//GL/GLProgram.h include//GL/GLScene.h include//GL/GLShaderFactory.h include//GL/GLSquareObjectCreator.h include//GL/GLTexture.h include//GL/GLTexture1Obj.h include//GL/GLTextureMatrixWork.h include//GL/GLTextureMultiObj.h include//GL/GLTextureWork.h include//GL/GLTransformer.h include//GL/GLTreeDrawWork.h include//GL/GLvboBuffer.h include//GL/GLvboBufferManager.h include//GL/GLWork.h include//GL/GLWorkHandler.h include//GL/GLWorkThread.h include//GL/head.h include//GL/IGLDrawWork.h include//GL/OpenGLWorker.h include//interface/GLColor.h include//interface/head.h include//interface/IBasicVarying.h include//interface/IBitmap.h include//interface/IFragmentFunction.h include//interface/IRasterizatedVarying.h include//interface/IVarying.h include//interface/IVertexFunction.h include//math/AbstractPoint.h include//math/BasicFunctionDeter.h include//math/FormulaTree.h include//math/FunctionDeter.h include//math/GLCurveSurface.h include//math/GLMatrix4.h include//math/GLSphere.h include//math/GLVector.h include//math/IFunctionDeter.h include//package/basic.h include//package/DefaultFunctionTable.h include//package/fragment.h include//package/GLPackage.h include//package/package.h include//package/vertex.h include//test/GLTest.h include//transform/GLBasicTransform.h include//transform/GLColorMap.h include//transform/GLFragPicture.h include//utils/ALClock.h include//utils/ALStream.h include//utils/GLAutoStorage.h include//utils/GLDebug.h include//utils/GLDefer.h include//utils/GLLock.h include//utils/GLMemoryPool.h include//utils/GLOnceWork.h include//utils/GLThread.h include//utils/GP_Clock.h include//utils/GPRandom.h include//utils/RefCount.h include//vertex/GL_Normal.h include//vertex/GL_position.h include//vertex/GL_texcord.h include//vertex/GLAbstractVarying.h include//vertex/GLVectorVarying.h include//AllShader.h include//asset/GLBasicMesh.h include//asset/GLIAsset.h include//asset/GLLightObjAsset.h include//core/GLBitmapFactory.h include//core/GLBmp.h include//core/GLDepthBuffer.h include//core/GLDynamicBitmap.h include//core/GLGrayBitmap.h include//core/GLRasterization.h include//core/GLRect.h include//fragment/GL_FragColor.h include//fragment/GL_FragPosition.h include//fragment/GL_FragTexcord.h include//fragment/GL_vPosition.h include//fragment/GLAbstractRasterizatedVarying.h include//fragment/GLLightFunction.h include//fragment/GLTexture2D.h include//fragment/GLWritePixels.h include//GL/debug.h include//GL/GLAutoFbo.h include//GL/GLAutoProgram.h include//GL/GLBasic3DObject.h include//GL/GLBezier.h include//GL/GLBiCubicCurveObj.h include//GL/GLBicubicWork.h include//GL/GLBitmapWork.h include//GL/GLBitmapWorkFactory.h include//GL/GLCamera.h include//GL/GLContext.h include//GL/GLCurveObject.h include//GL/GLCurveObjectFactory.h include//GL/GLDrawWork.h include//GL/GLFilterWork.h include//GL/GLFixScaleDrawWork.h include//GL/GLLightCurveObj.h include//GL/GLLightScene.h include//GL/GLMixWork.h include//GL/GLMultiBitmapWork.h include//GL/GLMultiPassDrawWork.h include//GL/GLMultiPassWork.h include//GL/GLObject.h include//GL/GLProgram.h include//GL/GLScene.h include//GL/GLShaderFactory.h include//GL/GLSquareObjectCreator.h include//GL/GLTexture.h include//GL/GLTexture1Obj.h include//GL/GLTextureMatrixWork.h include//GL/GLTextureMultiObj.h include//GL/GLTextureWork.h include//GL/GLTransformer.h include//GL/GLTreeDrawWork.h include//GL/GLvboBuffer.h include//GL/GLvboBufferManager.h include//GL/GLWork.h include//GL/GLWorkHandler.h include//GL/GLWorkThread.h include//GL/head.h include//GL/IGLDrawWork.h include//GL/OpenGLWorker.h include//interface/GLColor.h include//interface/head.h include//interface/IBasicVarying.h include//interface/IBitmap.h include//interface/IFragmentFunction.h include//interface/IRasterizatedVarying.h include//interface/IVarying.h include//interface/IVertexFunction.h include//math/AbstractPoint.h include//math/BasicFunctionDeter.h include//math/FormulaTree.h include//math/FunctionDeter.h include//math/GLCurveSurface.h include//math/GLMatrix4.h include//math/GLSphere.h include//math/GLVector.h include//math/IFunctionDeter.h include//package/basic.h include//package/DefaultFunctionTable.h include//package/fragment.h include//package/GLPackage.h include//package/package.h include//package/vertex.h include//test/GLTest.h include//transform/GLBasicTransform.h include//transform/GLColorMap.h include//transform/GLFragPicture.h include//utils/ALClock.h include//utils/ALStream.h include//utils/GLAutoStorage.h include//utils/GLDebug.h include//utils/GLDefer.h include//utils/GLLock.h include//utils/GLMemoryPool.h include//utils/GLOnceWork.h include//utils/GLThread.h include//utils/GP_Clock.h include//utils/GPRandom.h include//utils/RefCount.h include//vertex/GL_Normal.h include//vertex/GL_position.h include//vertex/GL_texcord.h include//vertex/GLAbstractVarying.h include//vertex/GLVectorVarying.h

libglsl.so:  build/src_asset_GLBasicMesh_cpp.o build/src_asset_GLLightObjAsset_cpp.o build/src_core_GLBitmapFactory_cpp.o build/src_core_GLBmp_cpp.o build/src_core_GLDepthBuffer_cpp.o build/src_core_GLDynamicBitmap_cpp.o build/src_core_GLGrayBitmap_cpp.o build/src_core_GLRasterization_cpp.o build/src_core_GLRect_cpp.o build/src_core_weightTable_cpp.o build/src_fragment_GLAbstractRasterizatedVarying_cpp.o build/src_fragment_GLLightFunction_cpp.o build/src_fragment_GLWritePixels_cpp.o build/src_fragment_texture2D_cpp.o build/src_GL_GLAutoFbo_cpp.o build/src_GL_GLAutoProgram_cpp.o build/src_GL_GLBasic3DObject_cpp.o build/src_GL_GLBezier_cpp.o build/src_GL_GLBiCubicCurveObj_cpp.o build/src_GL_GLBicubicWork_cpp.o build/src_GL_GLBitmapWork_cpp.o build/src_GL_GLBitmapWorkFactory_cpp.o build/src_GL_GLCamera_cpp.o build/src_GL_GLCurveObject_cpp.o build/src_GL_GLCurveObjectFactory_cpp.o build/src_GL_GLDrawWork_cpp.o build/src_GL_GLFilterWork_cpp.o build/src_GL_GLFixScaleDrawWork_cpp.o build/src_GL_GLFraction_cpp.o build/src_GL_GLLightCurveObject_cpp.o build/src_GL_GLLightScene_cpp.o build/src_GL_GLMixWork_cpp.o build/src_GL_GLMultiBitmapWork_cpp.o build/src_GL_GLMultiPassDrawWork_cpp.o build/src_GL_GLMultiPassWork_cpp.o build/src_GL_GLProgram_cpp.o build/src_GL_GLScene_cpp.o build/src_GL_GLShaderFactory_cpp.o build/src_GL_GLSquareObjectCreator_cpp.o build/src_GL_GLTexture_cpp.o build/src_GL_GLTexture1Obj_cpp.o build/src_GL_GLTextureMatrixWork_cpp.o build/src_GL_GLTextureWork_cpp.o build/src_GL_GLTreeDrawWork_cpp.o build/src_GL_GLvboBuffer_cpp.o build/src_GL_GLvboBufferManager_cpp.o build/src_GL_GLWorkThread_cpp.o build/src_GL_IGLDrawWork_cpp.o build/src_GL_OpenGLWorker_cpp.o build/src_math_AbstractPoint_cpp.o build/src_math_BasicFunctionDeter_cpp.o build/src_math_FormulaTree_cpp.o build/src_math_GLMatrix4_cpp.o build/src_math_GLSphere_cpp.o build/src_math_GLVector_cpp.o build/src_package_DefaultFunctionTable_cpp.o build/src_package_fragment_cpp.o build/src_package_GPPackage_cpp.o build/src_package_GPTypes_cpp.o build/src_platform_GLContext_cpp.o build/src_platform_GLLock_cpp.o build/src_transform_ColorMover_cpp.o build/src_transform_GLBasicTransform_cpp.o build/src_transform_GLColorMap_cpp.o build/src_transform_GLFragPicture_cpp.o build/src_transform_SceneNewton_cpp.o build/src_utils_ALFileStream_cpp.o build/src_utils_ALStream_cpp.o build/src_utils_GLOnceWork_cpp.o build/src_utils_GLThread_cpp.o build/src_utils_GP_Clock_cpp.o build/src_utils_GPRandom_cpp.o build/src_vertex_GL_Normal_cpp.o build/src_vertex_GL_position_cpp.o build/src_vertex_GLAbstractVarying_cpp.o build/src_vertex_GLVectorVarying_cpp.o build/glsl_AllShader_cpp.o build/src_utils_debug_c.o build/src_utils_GLMemoryPool_c.o 
	g++ -std=c++11   build/src_asset_GLBasicMesh_cpp.o build/src_asset_GLLightObjAsset_cpp.o build/src_core_GLBitmapFactory_cpp.o build/src_core_GLBmp_cpp.o build/src_core_GLDepthBuffer_cpp.o build/src_core_GLDynamicBitmap_cpp.o build/src_core_GLGrayBitmap_cpp.o build/src_core_GLRasterization_cpp.o build/src_core_GLRect_cpp.o build/src_core_weightTable_cpp.o build/src_fragment_GLAbstractRasterizatedVarying_cpp.o build/src_fragment_GLLightFunction_cpp.o build/src_fragment_GLWritePixels_cpp.o build/src_fragment_texture2D_cpp.o build/src_GL_GLAutoFbo_cpp.o build/src_GL_GLAutoProgram_cpp.o build/src_GL_GLBasic3DObject_cpp.o build/src_GL_GLBezier_cpp.o build/src_GL_GLBiCubicCurveObj_cpp.o build/src_GL_GLBicubicWork_cpp.o build/src_GL_GLBitmapWork_cpp.o build/src_GL_GLBitmapWorkFactory_cpp.o build/src_GL_GLCamera_cpp.o build/src_GL_GLCurveObject_cpp.o build/src_GL_GLCurveObjectFactory_cpp.o build/src_GL_GLDrawWork_cpp.o build/src_GL_GLFilterWork_cpp.o build/src_GL_GLFixScaleDrawWork_cpp.o build/src_GL_GLFraction_cpp.o build/src_GL_GLLightCurveObject_cpp.o build/src_GL_GLLightScene_cpp.o build/src_GL_GLMixWork_cpp.o build/src_GL_GLMultiBitmapWork_cpp.o build/src_GL_GLMultiPassDrawWork_cpp.o build/src_GL_GLMultiPassWork_cpp.o build/src_GL_GLProgram_cpp.o build/src_GL_GLScene_cpp.o build/src_GL_GLShaderFactory_cpp.o build/src_GL_GLSquareObjectCreator_cpp.o build/src_GL_GLTexture_cpp.o build/src_GL_GLTexture1Obj_cpp.o build/src_GL_GLTextureMatrixWork_cpp.o build/src_GL_GLTextureWork_cpp.o build/src_GL_GLTreeDrawWork_cpp.o build/src_GL_GLvboBuffer_cpp.o build/src_GL_GLvboBufferManager_cpp.o build/src_GL_GLWorkThread_cpp.o build/src_GL_IGLDrawWork_cpp.o build/src_GL_OpenGLWorker_cpp.o build/src_math_AbstractPoint_cpp.o build/src_math_BasicFunctionDeter_cpp.o build/src_math_FormulaTree_cpp.o build/src_math_GLMatrix4_cpp.o build/src_math_GLSphere_cpp.o build/src_math_GLVector_cpp.o build/src_package_DefaultFunctionTable_cpp.o build/src_package_fragment_cpp.o build/src_package_GPPackage_cpp.o build/src_package_GPTypes_cpp.o build/src_platform_GLContext_cpp.o build/src_platform_GLLock_cpp.o build/src_transform_ColorMover_cpp.o build/src_transform_GLBasicTransform_cpp.o build/src_transform_GLColorMap_cpp.o build/src_transform_GLFragPicture_cpp.o build/src_transform_SceneNewton_cpp.o build/src_utils_ALFileStream_cpp.o build/src_utils_ALStream_cpp.o build/src_utils_GLOnceWork_cpp.o build/src_utils_GLThread_cpp.o build/src_utils_GP_Clock_cpp.o build/src_utils_GPRandom_cpp.o build/src_vertex_GL_Normal_cpp.o build/src_vertex_GL_position_cpp.o build/src_vertex_GLAbstractVarying_cpp.o build/src_vertex_GLVectorVarying_cpp.o build/glsl_AllShader_cpp.o build/src_utils_debug_c.o build/src_utils_GLMemoryPool_c.o -O3 -g -fPIC  --shared   ./third_party/FreeImage/libfreeimage.a -framework OpenGL -framework GLUT -framework AGL -o libglsl.so ${SELF_VARIABLES}
build/src_asset_GLBasicMesh_cpp.o : src/asset/GLBasicMesh.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_asset_GLBasicMesh_cpp.o -c src/asset/GLBasicMesh.cpp -Iinclude -I../Renascence/include/
  
build/src_asset_GLLightObjAsset_cpp.o : src/asset/GLLightObjAsset.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_asset_GLLightObjAsset_cpp.o -c src/asset/GLLightObjAsset.cpp -Iinclude -I../Renascence/include/
  
build/src_core_GLBitmapFactory_cpp.o : src/core/GLBitmapFactory.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_core_GLBitmapFactory_cpp.o -c src/core/GLBitmapFactory.cpp -Iinclude -I../Renascence/include/
  
build/src_core_GLBmp_cpp.o : src/core/GLBmp.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_core_GLBmp_cpp.o -c src/core/GLBmp.cpp -Iinclude -I../Renascence/include/
  
build/src_core_GLDepthBuffer_cpp.o : src/core/GLDepthBuffer.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_core_GLDepthBuffer_cpp.o -c src/core/GLDepthBuffer.cpp -Iinclude -I../Renascence/include/
  
build/src_core_GLDynamicBitmap_cpp.o : src/core/GLDynamicBitmap.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_core_GLDynamicBitmap_cpp.o -c src/core/GLDynamicBitmap.cpp -Iinclude -I../Renascence/include/
  
build/src_core_GLGrayBitmap_cpp.o : src/core/GLGrayBitmap.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_core_GLGrayBitmap_cpp.o -c src/core/GLGrayBitmap.cpp -Iinclude -I../Renascence/include/
  
build/src_core_GLRasterization_cpp.o : src/core/GLRasterization.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_core_GLRasterization_cpp.o -c src/core/GLRasterization.cpp -Iinclude -I../Renascence/include/
  
build/src_core_GLRect_cpp.o : src/core/GLRect.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_core_GLRect_cpp.o -c src/core/GLRect.cpp -Iinclude -I../Renascence/include/
  
build/src_core_weightTable_cpp.o : src/core/weightTable.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_core_weightTable_cpp.o -c src/core/weightTable.cpp -Iinclude -I../Renascence/include/
  
build/src_fragment_GLAbstractRasterizatedVarying_cpp.o : src/fragment/GLAbstractRasterizatedVarying.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_fragment_GLAbstractRasterizatedVarying_cpp.o -c src/fragment/GLAbstractRasterizatedVarying.cpp -Iinclude -I../Renascence/include/
  
build/src_fragment_GLLightFunction_cpp.o : src/fragment/GLLightFunction.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_fragment_GLLightFunction_cpp.o -c src/fragment/GLLightFunction.cpp -Iinclude -I../Renascence/include/
  
build/src_fragment_GLWritePixels_cpp.o : src/fragment/GLWritePixels.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_fragment_GLWritePixels_cpp.o -c src/fragment/GLWritePixels.cpp -Iinclude -I../Renascence/include/
  
build/src_fragment_texture2D_cpp.o : src/fragment/texture2D.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_fragment_texture2D_cpp.o -c src/fragment/texture2D.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLAutoFbo_cpp.o : src/GL/GLAutoFbo.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLAutoFbo_cpp.o -c src/GL/GLAutoFbo.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLAutoProgram_cpp.o : src/GL/GLAutoProgram.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLAutoProgram_cpp.o -c src/GL/GLAutoProgram.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLBasic3DObject_cpp.o : src/GL/GLBasic3DObject.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLBasic3DObject_cpp.o -c src/GL/GLBasic3DObject.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLBezier_cpp.o : src/GL/GLBezier.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLBezier_cpp.o -c src/GL/GLBezier.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLBiCubicCurveObj_cpp.o : src/GL/GLBiCubicCurveObj.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLBiCubicCurveObj_cpp.o -c src/GL/GLBiCubicCurveObj.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLBicubicWork_cpp.o : src/GL/GLBicubicWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLBicubicWork_cpp.o -c src/GL/GLBicubicWork.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLBitmapWork_cpp.o : src/GL/GLBitmapWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLBitmapWork_cpp.o -c src/GL/GLBitmapWork.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLBitmapWorkFactory_cpp.o : src/GL/GLBitmapWorkFactory.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLBitmapWorkFactory_cpp.o -c src/GL/GLBitmapWorkFactory.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLCamera_cpp.o : src/GL/GLCamera.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLCamera_cpp.o -c src/GL/GLCamera.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLCurveObject_cpp.o : src/GL/GLCurveObject.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLCurveObject_cpp.o -c src/GL/GLCurveObject.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLCurveObjectFactory_cpp.o : src/GL/GLCurveObjectFactory.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLCurveObjectFactory_cpp.o -c src/GL/GLCurveObjectFactory.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLDrawWork_cpp.o : src/GL/GLDrawWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLDrawWork_cpp.o -c src/GL/GLDrawWork.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLFilterWork_cpp.o : src/GL/GLFilterWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLFilterWork_cpp.o -c src/GL/GLFilterWork.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLFixScaleDrawWork_cpp.o : src/GL/GLFixScaleDrawWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLFixScaleDrawWork_cpp.o -c src/GL/GLFixScaleDrawWork.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLFraction_cpp.o : src/GL/GLFraction.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLFraction_cpp.o -c src/GL/GLFraction.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLLightCurveObject_cpp.o : src/GL/GLLightCurveObject.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLLightCurveObject_cpp.o -c src/GL/GLLightCurveObject.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLLightScene_cpp.o : src/GL/GLLightScene.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLLightScene_cpp.o -c src/GL/GLLightScene.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLMixWork_cpp.o : src/GL/GLMixWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLMixWork_cpp.o -c src/GL/GLMixWork.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLMultiBitmapWork_cpp.o : src/GL/GLMultiBitmapWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLMultiBitmapWork_cpp.o -c src/GL/GLMultiBitmapWork.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLMultiPassDrawWork_cpp.o : src/GL/GLMultiPassDrawWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLMultiPassDrawWork_cpp.o -c src/GL/GLMultiPassDrawWork.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLMultiPassWork_cpp.o : src/GL/GLMultiPassWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLMultiPassWork_cpp.o -c src/GL/GLMultiPassWork.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLProgram_cpp.o : src/GL/GLProgram.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLProgram_cpp.o -c src/GL/GLProgram.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLScene_cpp.o : src/GL/GLScene.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLScene_cpp.o -c src/GL/GLScene.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLShaderFactory_cpp.o : src/GL/GLShaderFactory.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLShaderFactory_cpp.o -c src/GL/GLShaderFactory.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLSquareObjectCreator_cpp.o : src/GL/GLSquareObjectCreator.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLSquareObjectCreator_cpp.o -c src/GL/GLSquareObjectCreator.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLTexture_cpp.o : src/GL/GLTexture.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLTexture_cpp.o -c src/GL/GLTexture.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLTexture1Obj_cpp.o : src/GL/GLTexture1Obj.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLTexture1Obj_cpp.o -c src/GL/GLTexture1Obj.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLTextureMatrixWork_cpp.o : src/GL/GLTextureMatrixWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLTextureMatrixWork_cpp.o -c src/GL/GLTextureMatrixWork.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLTextureWork_cpp.o : src/GL/GLTextureWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLTextureWork_cpp.o -c src/GL/GLTextureWork.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLTreeDrawWork_cpp.o : src/GL/GLTreeDrawWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLTreeDrawWork_cpp.o -c src/GL/GLTreeDrawWork.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLvboBuffer_cpp.o : src/GL/GLvboBuffer.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLvboBuffer_cpp.o -c src/GL/GLvboBuffer.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLvboBufferManager_cpp.o : src/GL/GLvboBufferManager.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLvboBufferManager_cpp.o -c src/GL/GLvboBufferManager.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_GLWorkThread_cpp.o : src/GL/GLWorkThread.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_GLWorkThread_cpp.o -c src/GL/GLWorkThread.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_IGLDrawWork_cpp.o : src/GL/IGLDrawWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_IGLDrawWork_cpp.o -c src/GL/IGLDrawWork.cpp -Iinclude -I../Renascence/include/
  
build/src_GL_OpenGLWorker_cpp.o : src/GL/OpenGLWorker.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_GL_OpenGLWorker_cpp.o -c src/GL/OpenGLWorker.cpp -Iinclude -I../Renascence/include/
  
build/src_math_AbstractPoint_cpp.o : src/math/AbstractPoint.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_math_AbstractPoint_cpp.o -c src/math/AbstractPoint.cpp -Iinclude -I../Renascence/include/
  
build/src_math_BasicFunctionDeter_cpp.o : src/math/BasicFunctionDeter.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_math_BasicFunctionDeter_cpp.o -c src/math/BasicFunctionDeter.cpp -Iinclude -I../Renascence/include/
  
build/src_math_FormulaTree_cpp.o : src/math/FormulaTree.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_math_FormulaTree_cpp.o -c src/math/FormulaTree.cpp -Iinclude -I../Renascence/include/
  
build/src_math_GLMatrix4_cpp.o : src/math/GLMatrix4.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_math_GLMatrix4_cpp.o -c src/math/GLMatrix4.cpp -Iinclude -I../Renascence/include/
  
build/src_math_GLSphere_cpp.o : src/math/GLSphere.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_math_GLSphere_cpp.o -c src/math/GLSphere.cpp -Iinclude -I../Renascence/include/
  
build/src_math_GLVector_cpp.o : src/math/GLVector.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_math_GLVector_cpp.o -c src/math/GLVector.cpp -Iinclude -I../Renascence/include/
  
build/src_package_DefaultFunctionTable_cpp.o : src/package/DefaultFunctionTable.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_package_DefaultFunctionTable_cpp.o -c src/package/DefaultFunctionTable.cpp -Iinclude -I../Renascence/include/
  
build/src_package_fragment_cpp.o : src/package/fragment.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_package_fragment_cpp.o -c src/package/fragment.cpp -Iinclude -I../Renascence/include/
  
build/src_package_GPPackage_cpp.o : src/package/GPPackage.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_package_GPPackage_cpp.o -c src/package/GPPackage.cpp -Iinclude -I../Renascence/include/
  
build/src_package_GPTypes_cpp.o : src/package/GPTypes.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_package_GPTypes_cpp.o -c src/package/GPTypes.cpp -Iinclude -I../Renascence/include/
  
build/src_platform_GLContext_cpp.o : src/platform/GLContext.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_platform_GLContext_cpp.o -c src/platform/GLContext.cpp -Iinclude -I../Renascence/include/
  
build/src_platform_GLLock_cpp.o : src/platform/GLLock.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_platform_GLLock_cpp.o -c src/platform/GLLock.cpp -Iinclude -I../Renascence/include/
  
build/src_transform_ColorMover_cpp.o : src/transform/ColorMover.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_transform_ColorMover_cpp.o -c src/transform/ColorMover.cpp -Iinclude -I../Renascence/include/
  
build/src_transform_GLBasicTransform_cpp.o : src/transform/GLBasicTransform.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_transform_GLBasicTransform_cpp.o -c src/transform/GLBasicTransform.cpp -Iinclude -I../Renascence/include/
  
build/src_transform_GLColorMap_cpp.o : src/transform/GLColorMap.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_transform_GLColorMap_cpp.o -c src/transform/GLColorMap.cpp -Iinclude -I../Renascence/include/
  
build/src_transform_GLFragPicture_cpp.o : src/transform/GLFragPicture.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_transform_GLFragPicture_cpp.o -c src/transform/GLFragPicture.cpp -Iinclude -I../Renascence/include/
  
build/src_transform_SceneNewton_cpp.o : src/transform/SceneNewton.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_transform_SceneNewton_cpp.o -c src/transform/SceneNewton.cpp -Iinclude -I../Renascence/include/
  
build/src_utils_ALFileStream_cpp.o : src/utils/ALFileStream.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_utils_ALFileStream_cpp.o -c src/utils/ALFileStream.cpp -Iinclude -I../Renascence/include/
  
build/src_utils_ALStream_cpp.o : src/utils/ALStream.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_utils_ALStream_cpp.o -c src/utils/ALStream.cpp -Iinclude -I../Renascence/include/
  
build/src_utils_GLOnceWork_cpp.o : src/utils/GLOnceWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_utils_GLOnceWork_cpp.o -c src/utils/GLOnceWork.cpp -Iinclude -I../Renascence/include/
  
build/src_utils_GLThread_cpp.o : src/utils/GLThread.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_utils_GLThread_cpp.o -c src/utils/GLThread.cpp -Iinclude -I../Renascence/include/
  
build/src_utils_GP_Clock_cpp.o : src/utils/GP_Clock.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_utils_GP_Clock_cpp.o -c src/utils/GP_Clock.cpp -Iinclude -I../Renascence/include/
  
build/src_utils_GPRandom_cpp.o : src/utils/GPRandom.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_utils_GPRandom_cpp.o -c src/utils/GPRandom.cpp -Iinclude -I../Renascence/include/
  
build/src_vertex_GL_Normal_cpp.o : src/vertex/GL_Normal.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_vertex_GL_Normal_cpp.o -c src/vertex/GL_Normal.cpp -Iinclude -I../Renascence/include/
  
build/src_vertex_GL_position_cpp.o : src/vertex/GL_position.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_vertex_GL_position_cpp.o -c src/vertex/GL_position.cpp -Iinclude -I../Renascence/include/
  
build/src_vertex_GLAbstractVarying_cpp.o : src/vertex/GLAbstractVarying.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_vertex_GLAbstractVarying_cpp.o -c src/vertex/GLAbstractVarying.cpp -Iinclude -I../Renascence/include/
  
build/src_vertex_GLVectorVarying_cpp.o : src/vertex/GLVectorVarying.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_vertex_GLVectorVarying_cpp.o -c src/vertex/GLVectorVarying.cpp -Iinclude -I../Renascence/include/
  
build/glsl_AllShader_cpp.o : glsl/AllShader.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/glsl_AllShader_cpp.o -c glsl/AllShader.cpp -Iinclude -I../Renascence/include/
  
build/src_utils_debug_c.o : src/utils/debug.c   ${ALL_INCLUESlibglsl.so}
	gcc -std=c11 -O3 -g -fPIC -o build/src_utils_debug_c.o -c src/utils/debug.c -Iinclude -I../Renascence/include/
  
build/src_utils_GLMemoryPool_c.o : src/utils/GLMemoryPool.c   ${ALL_INCLUESlibglsl.so}
	gcc -std=c11 -O3 -g -fPIC -o build/src_utils_GLMemoryPool_c.o -c src/utils/GLMemoryPool.c -Iinclude -I../Renascence/include/
  

ALL_INCLUEStest.out= include//AllShader.h include//asset/GLBasicMesh.h include//asset/GLIAsset.h include//asset/GLLightObjAsset.h include//core/GLBitmapFactory.h include//core/GLBmp.h include//core/GLDepthBuffer.h include//core/GLDynamicBitmap.h include//core/GLGrayBitmap.h include//core/GLRasterization.h include//core/GLRect.h include//fragment/GL_FragColor.h include//fragment/GL_FragPosition.h include//fragment/GL_FragTexcord.h include//fragment/GL_vPosition.h include//fragment/GLAbstractRasterizatedVarying.h include//fragment/GLLightFunction.h include//fragment/GLTexture2D.h include//fragment/GLWritePixels.h include//GL/debug.h include//GL/GLAutoFbo.h include//GL/GLAutoProgram.h include//GL/GLBasic3DObject.h include//GL/GLBezier.h include//GL/GLBiCubicCurveObj.h include//GL/GLBicubicWork.h include//GL/GLBitmapWork.h include//GL/GLBitmapWorkFactory.h include//GL/GLCamera.h include//GL/GLContext.h include//GL/GLCurveObject.h include//GL/GLCurveObjectFactory.h include//GL/GLDrawWork.h include//GL/GLFilterWork.h include//GL/GLFixScaleDrawWork.h include//GL/GLLightCurveObj.h include//GL/GLLightScene.h include//GL/GLMixWork.h include//GL/GLMultiBitmapWork.h include//GL/GLMultiPassDrawWork.h include//GL/GLMultiPassWork.h include//GL/GLObject.h include//GL/GLProgram.h include//GL/GLScene.h include//GL/GLShaderFactory.h include//GL/GLSquareObjectCreator.h include//GL/GLTexture.h include//GL/GLTexture1Obj.h include//GL/GLTextureMatrixWork.h include//GL/GLTextureMultiObj.h include//GL/GLTextureWork.h include//GL/GLTransformer.h include//GL/GLTreeDrawWork.h include//GL/GLvboBuffer.h include//GL/GLvboBufferManager.h include//GL/GLWork.h include//GL/GLWorkHandler.h include//GL/GLWorkThread.h include//GL/head.h include//GL/IGLDrawWork.h include//GL/OpenGLWorker.h include//interface/GLColor.h include//interface/head.h include//interface/IBasicVarying.h include//interface/IBitmap.h include//interface/IFragmentFunction.h include//interface/IRasterizatedVarying.h include//interface/IVarying.h include//interface/IVertexFunction.h include//math/AbstractPoint.h include//math/BasicFunctionDeter.h include//math/FormulaTree.h include//math/FunctionDeter.h include//math/GLCurveSurface.h include//math/GLMatrix4.h include//math/GLSphere.h include//math/GLVector.h include//math/IFunctionDeter.h include//package/basic.h include//package/DefaultFunctionTable.h include//package/fragment.h include//package/GLPackage.h include//package/package.h include//package/vertex.h include//test/GLTest.h include//transform/GLBasicTransform.h include//transform/GLColorMap.h include//transform/GLFragPicture.h include//utils/ALClock.h include//utils/ALStream.h include//utils/GLAutoStorage.h include//utils/GLDebug.h include//utils/GLDefer.h include//utils/GLLock.h include//utils/GLMemoryPool.h include//utils/GLOnceWork.h include//utils/GLThread.h include//utils/GP_Clock.h include//utils/GPRandom.h include//utils/RefCount.h include//vertex/GL_Normal.h include//vertex/GL_position.h include//vertex/GL_texcord.h include//vertex/GLAbstractVarying.h include//vertex/GLVectorVarying.h

test.out:  build/test_GLBitmapFactoryTest_cpp.o build/test_GLBmpTest_cpp.o build/test_GLColorMapTest_cpp.o build/test_GLFragTest_cpp.o build/test_GLGrayTest_cpp.o build/test_GLProjectionTest_cpp.o build/test_GLRasterBasic_cpp.o build/test_GLRotateTest_cpp.o build/test_GLSingleLightTest_cpp.o build/test_GLTest_cpp.o build/test_main_cpp.o libglsl.so
	g++ -std=c++11   build/test_GLBitmapFactoryTest_cpp.o build/test_GLBmpTest_cpp.o build/test_GLColorMapTest_cpp.o build/test_GLFragTest_cpp.o build/test_GLGrayTest_cpp.o build/test_GLProjectionTest_cpp.o build/test_GLRasterBasic_cpp.o build/test_GLRotateTest_cpp.o build/test_GLSingleLightTest_cpp.o build/test_GLTest_cpp.o build/test_main_cpp.o -O3 -g -fPIC   ./libglsl.so -o test.out ${SELF_VARIABLES}
build/test_GLBitmapFactoryTest_cpp.o : test/GLBitmapFactoryTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GLBitmapFactoryTest_cpp.o -c test/GLBitmapFactoryTest.cpp -Iinclude -I../Renascence/include/
  
build/test_GLBmpTest_cpp.o : test/GLBmpTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GLBmpTest_cpp.o -c test/GLBmpTest.cpp -Iinclude -I../Renascence/include/
  
build/test_GLColorMapTest_cpp.o : test/GLColorMapTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GLColorMapTest_cpp.o -c test/GLColorMapTest.cpp -Iinclude -I../Renascence/include/
  
build/test_GLFragTest_cpp.o : test/GLFragTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GLFragTest_cpp.o -c test/GLFragTest.cpp -Iinclude -I../Renascence/include/
  
build/test_GLGrayTest_cpp.o : test/GLGrayTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GLGrayTest_cpp.o -c test/GLGrayTest.cpp -Iinclude -I../Renascence/include/
  
build/test_GLProjectionTest_cpp.o : test/GLProjectionTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GLProjectionTest_cpp.o -c test/GLProjectionTest.cpp -Iinclude -I../Renascence/include/
  
build/test_GLRasterBasic_cpp.o : test/GLRasterBasic.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GLRasterBasic_cpp.o -c test/GLRasterBasic.cpp -Iinclude -I../Renascence/include/
  
build/test_GLRotateTest_cpp.o : test/GLRotateTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GLRotateTest_cpp.o -c test/GLRotateTest.cpp -Iinclude -I../Renascence/include/
  
build/test_GLSingleLightTest_cpp.o : test/GLSingleLightTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GLSingleLightTest_cpp.o -c test/GLSingleLightTest.cpp -Iinclude -I../Renascence/include/
  
build/test_GLTest_cpp.o : test/GLTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GLTest_cpp.o -c test/GLTest.cpp -Iinclude -I../Renascence/include/
  
build/test_main_cpp.o : test/main.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_main_cpp.o -c test/main.cpp -Iinclude -I../Renascence/include/
  

ALL_INCLUESgputest.out= include//AllShader.h include//asset/GLBasicMesh.h include//asset/GLIAsset.h include//asset/GLLightObjAsset.h include//core/GLBitmapFactory.h include//core/GLBmp.h include//core/GLDepthBuffer.h include//core/GLDynamicBitmap.h include//core/GLGrayBitmap.h include//core/GLRasterization.h include//core/GLRect.h include//fragment/GL_FragColor.h include//fragment/GL_FragPosition.h include//fragment/GL_FragTexcord.h include//fragment/GL_vPosition.h include//fragment/GLAbstractRasterizatedVarying.h include//fragment/GLLightFunction.h include//fragment/GLTexture2D.h include//fragment/GLWritePixels.h include//GL/debug.h include//GL/GLAutoFbo.h include//GL/GLAutoProgram.h include//GL/GLBasic3DObject.h include//GL/GLBezier.h include//GL/GLBiCubicCurveObj.h include//GL/GLBicubicWork.h include//GL/GLBitmapWork.h include//GL/GLBitmapWorkFactory.h include//GL/GLCamera.h include//GL/GLContext.h include//GL/GLCurveObject.h include//GL/GLCurveObjectFactory.h include//GL/GLDrawWork.h include//GL/GLFilterWork.h include//GL/GLFixScaleDrawWork.h include//GL/GLLightCurveObj.h include//GL/GLLightScene.h include//GL/GLMixWork.h include//GL/GLMultiBitmapWork.h include//GL/GLMultiPassDrawWork.h include//GL/GLMultiPassWork.h include//GL/GLObject.h include//GL/GLProgram.h include//GL/GLScene.h include//GL/GLShaderFactory.h include//GL/GLSquareObjectCreator.h include//GL/GLTexture.h include//GL/GLTexture1Obj.h include//GL/GLTextureMatrixWork.h include//GL/GLTextureMultiObj.h include//GL/GLTextureWork.h include//GL/GLTransformer.h include//GL/GLTreeDrawWork.h include//GL/GLvboBuffer.h include//GL/GLvboBufferManager.h include//GL/GLWork.h include//GL/GLWorkHandler.h include//GL/GLWorkThread.h include//GL/head.h include//GL/IGLDrawWork.h include//GL/OpenGLWorker.h include//interface/GLColor.h include//interface/head.h include//interface/IBasicVarying.h include//interface/IBitmap.h include//interface/IFragmentFunction.h include//interface/IRasterizatedVarying.h include//interface/IVarying.h include//interface/IVertexFunction.h include//math/AbstractPoint.h include//math/BasicFunctionDeter.h include//math/FormulaTree.h include//math/FunctionDeter.h include//math/GLCurveSurface.h include//math/GLMatrix4.h include//math/GLSphere.h include//math/GLVector.h include//math/IFunctionDeter.h include//package/basic.h include//package/DefaultFunctionTable.h include//package/fragment.h include//package/GLPackage.h include//package/package.h include//package/vertex.h include//test/GLTest.h include//transform/GLBasicTransform.h include//transform/GLColorMap.h include//transform/GLFragPicture.h include//utils/ALClock.h include//utils/ALStream.h include//utils/GLAutoStorage.h include//utils/GLDebug.h include//utils/GLDefer.h include//utils/GLLock.h include//utils/GLMemoryPool.h include//utils/GLOnceWork.h include//utils/GLThread.h include//utils/GP_Clock.h include//utils/GPRandom.h include//utils/RefCount.h include//vertex/GL_Normal.h include//vertex/GL_position.h include//vertex/GL_texcord.h include//vertex/GLAbstractVarying.h include//vertex/GLVectorVarying.h

gputest.out:  build/gltest_GLBitmapWorkTest_cpp.o build/gltest_GLCubicTest_cpp.o build/gltest_GLFactoryTest_cpp.o build/gltest_GLFilterTest_cpp.o build/gltest_GLFractionByGLTest_cpp.o build/gltest_GLMixFractionTest_cpp.o build/gltest_GLMultiBitmapTest_cpp.o build/gltest_GLScalePSNRTest_cpp.o build/gltest_GLTest_cpp.o build/gltest_GLTextureMatrixWorkTest_cpp.o build/gltest_GLWorkThreadTest_cpp.o build/gltest_opengltest_main_cpp.o libglsl.so
	g++ -std=c++11   build/gltest_GLBitmapWorkTest_cpp.o build/gltest_GLCubicTest_cpp.o build/gltest_GLFactoryTest_cpp.o build/gltest_GLFilterTest_cpp.o build/gltest_GLFractionByGLTest_cpp.o build/gltest_GLMixFractionTest_cpp.o build/gltest_GLMultiBitmapTest_cpp.o build/gltest_GLScalePSNRTest_cpp.o build/gltest_GLTest_cpp.o build/gltest_GLTextureMatrixWorkTest_cpp.o build/gltest_GLWorkThreadTest_cpp.o build/gltest_opengltest_main_cpp.o -O3 -g -fPIC   ./libglsl.so -o gputest.out ${SELF_VARIABLES}
build/gltest_GLBitmapWorkTest_cpp.o : gltest/GLBitmapWorkTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/gltest_GLBitmapWorkTest_cpp.o -c gltest/GLBitmapWorkTest.cpp -Iinclude -I../Renascence/include/
  
build/gltest_GLCubicTest_cpp.o : gltest/GLCubicTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/gltest_GLCubicTest_cpp.o -c gltest/GLCubicTest.cpp -Iinclude -I../Renascence/include/
  
build/gltest_GLFactoryTest_cpp.o : gltest/GLFactoryTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/gltest_GLFactoryTest_cpp.o -c gltest/GLFactoryTest.cpp -Iinclude -I../Renascence/include/
  
build/gltest_GLFilterTest_cpp.o : gltest/GLFilterTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/gltest_GLFilterTest_cpp.o -c gltest/GLFilterTest.cpp -Iinclude -I../Renascence/include/
  
build/gltest_GLFractionByGLTest_cpp.o : gltest/GLFractionByGLTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/gltest_GLFractionByGLTest_cpp.o -c gltest/GLFractionByGLTest.cpp -Iinclude -I../Renascence/include/
  
build/gltest_GLMixFractionTest_cpp.o : gltest/GLMixFractionTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/gltest_GLMixFractionTest_cpp.o -c gltest/GLMixFractionTest.cpp -Iinclude -I../Renascence/include/
  
build/gltest_GLMultiBitmapTest_cpp.o : gltest/GLMultiBitmapTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/gltest_GLMultiBitmapTest_cpp.o -c gltest/GLMultiBitmapTest.cpp -Iinclude -I../Renascence/include/
  
build/gltest_GLScalePSNRTest_cpp.o : gltest/GLScalePSNRTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/gltest_GLScalePSNRTest_cpp.o -c gltest/GLScalePSNRTest.cpp -Iinclude -I../Renascence/include/
  
build/gltest_GLTest_cpp.o : gltest/GLTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/gltest_GLTest_cpp.o -c gltest/GLTest.cpp -Iinclude -I../Renascence/include/
  
build/gltest_GLTextureMatrixWorkTest_cpp.o : gltest/GLTextureMatrixWorkTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/gltest_GLTextureMatrixWorkTest_cpp.o -c gltest/GLTextureMatrixWorkTest.cpp -Iinclude -I../Renascence/include/
  
build/gltest_GLWorkThreadTest_cpp.o : gltest/GLWorkThreadTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/gltest_GLWorkThreadTest_cpp.o -c gltest/GLWorkThreadTest.cpp -Iinclude -I../Renascence/include/
  
build/gltest_opengltest_main_cpp.o : gltest/opengltest_main.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/gltest_opengltest_main_cpp.o -c gltest/opengltest_main.cpp -Iinclude -I../Renascence/include/
  

ALL_INCLUESexample.out= include//AllShader.h include//asset/GLBasicMesh.h include//asset/GLIAsset.h include//asset/GLLightObjAsset.h include//core/GLBitmapFactory.h include//core/GLBmp.h include//core/GLDepthBuffer.h include//core/GLDynamicBitmap.h include//core/GLGrayBitmap.h include//core/GLRasterization.h include//core/GLRect.h include//fragment/GL_FragColor.h include//fragment/GL_FragPosition.h include//fragment/GL_FragTexcord.h include//fragment/GL_vPosition.h include//fragment/GLAbstractRasterizatedVarying.h include//fragment/GLLightFunction.h include//fragment/GLTexture2D.h include//fragment/GLWritePixels.h include//GL/debug.h include//GL/GLAutoFbo.h include//GL/GLAutoProgram.h include//GL/GLBasic3DObject.h include//GL/GLBezier.h include//GL/GLBiCubicCurveObj.h include//GL/GLBicubicWork.h include//GL/GLBitmapWork.h include//GL/GLBitmapWorkFactory.h include//GL/GLCamera.h include//GL/GLContext.h include//GL/GLCurveObject.h include//GL/GLCurveObjectFactory.h include//GL/GLDrawWork.h include//GL/GLFilterWork.h include//GL/GLFixScaleDrawWork.h include//GL/GLLightCurveObj.h include//GL/GLLightScene.h include//GL/GLMixWork.h include//GL/GLMultiBitmapWork.h include//GL/GLMultiPassDrawWork.h include//GL/GLMultiPassWork.h include//GL/GLObject.h include//GL/GLProgram.h include//GL/GLScene.h include//GL/GLShaderFactory.h include//GL/GLSquareObjectCreator.h include//GL/GLTexture.h include//GL/GLTexture1Obj.h include//GL/GLTextureMatrixWork.h include//GL/GLTextureMultiObj.h include//GL/GLTextureWork.h include//GL/GLTransformer.h include//GL/GLTreeDrawWork.h include//GL/GLvboBuffer.h include//GL/GLvboBufferManager.h include//GL/GLWork.h include//GL/GLWorkHandler.h include//GL/GLWorkThread.h include//GL/head.h include//GL/IGLDrawWork.h include//GL/OpenGLWorker.h include//interface/GLColor.h include//interface/head.h include//interface/IBasicVarying.h include//interface/IBitmap.h include//interface/IFragmentFunction.h include//interface/IRasterizatedVarying.h include//interface/IVarying.h include//interface/IVertexFunction.h include//math/AbstractPoint.h include//math/BasicFunctionDeter.h include//math/FormulaTree.h include//math/FunctionDeter.h include//math/GLCurveSurface.h include//math/GLMatrix4.h include//math/GLSphere.h include//math/GLVector.h include//math/IFunctionDeter.h include//package/basic.h include//package/DefaultFunctionTable.h include//package/fragment.h include//package/GLPackage.h include//package/package.h include//package/vertex.h include//test/GLTest.h include//transform/GLBasicTransform.h include//transform/GLColorMap.h include//transform/GLFragPicture.h include//utils/ALClock.h include//utils/ALStream.h include//utils/GLAutoStorage.h include//utils/GLDebug.h include//utils/GLDefer.h include//utils/GLLock.h include//utils/GLMemoryPool.h include//utils/GLOnceWork.h include//utils/GLThread.h include//utils/GP_Clock.h include//utils/GPRandom.h include//utils/RefCount.h include//vertex/GL_Normal.h include//vertex/GL_position.h include//vertex/GL_texcord.h include//vertex/GLAbstractVarying.h include//vertex/GLVectorVarying.h

example.out:  build/example_main_cpp.o libglsl.so
	g++ -std=c++11   build/example_main_cpp.o -O3 -g -fPIC   ./libglsl.so -o example.out ${SELF_VARIABLES}
build/example_main_cpp.o : example/main.cpp libglsl.so  ${ALL_INCLUESexample.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/example_main_cpp.o -c example/main.cpp -Iinclude -I../Renascence/include/
  

ALL_INCLUESconvert_data.out=

convert_data.out:  build/convert_data_cpp.o libglsl.so
	g++ -std=c++11   build/convert_data_cpp.o -O3 -g -fPIC   ./libglsl.so -o convert_data.out ${SELF_VARIABLES}
build/convert_data_cpp.o : convert_data.cpp libglsl.so  ${ALL_INCLUESconvert_data.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/convert_data_cpp.o -c convert_data.cpp -Iinclude -I../Renascence/include/
  

ALL_INCLUESpicture_treat.out=

picture_treat.out:  build/picture_treat_cpp.o libglsl.so
	g++ -std=c++11   build/picture_treat_cpp.o -O3 -g -fPIC   ./libglsl.so -o picture_treat.out ${SELF_VARIABLES}
build/picture_treat_cpp.o : picture_treat.cpp libglsl.so  ${ALL_INCLUESpicture_treat.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/picture_treat_cpp.o -c picture_treat.cpp -Iinclude -I../Renascence/include/
  

ALL_INCLUESgp_color_table_data_make.out=

gp_color_table_data_make.out:  build/gp_color_table_data_make_cpp.o libglsl.so
	g++ -std=c++11   build/gp_color_table_data_make_cpp.o -O3 -g -fPIC   ./libglsl.so -o gp_color_table_data_make.out ${SELF_VARIABLES}
build/gp_color_table_data_make_cpp.o : gp_color_table_data_make.cpp libglsl.so  ${ALL_INCLUESgp_color_table_data_make.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/gp_color_table_data_make_cpp.o -c gp_color_table_data_make.cpp -Iinclude -I../Renascence/include/
  

ALL_INCLUEScolor_extract.out=

color_extract.out:  build/color_extract_cpp.o libglsl.so
	g++ -std=c++11   build/color_extract_cpp.o -O3 -g -fPIC   ./libglsl.so -o color_extract.out ${SELF_VARIABLES}
build/color_extract_cpp.o : color_extract.cpp libglsl.so  ${ALL_INCLUEScolor_extract.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/color_extract_cpp.o -c color_extract.cpp -Iinclude -I../Renascence/include/
  

ALL_INCLUESpicture_scale.out=

picture_scale.out:  build/picture_scale_cpp.o libglsl.so
	g++ -std=c++11   build/picture_scale_cpp.o -O3 -g -fPIC   ./libglsl.so -o picture_scale.out ${SELF_VARIABLES}
build/picture_scale_cpp.o : picture_scale.cpp libglsl.so  ${ALL_INCLUESpicture_scale.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/picture_scale_cpp.o -c picture_scale.cpp -Iinclude -I../Renascence/include/
  

clean:
	rm build/*.o
	rm libglsl.so
	rm test.out
	rm gputest.out
	rm example.out
	rm convert_data.out
	rm picture_treat.out
	rm gp_color_table_data_make.out
	rm color_extract.out
	rm picture_scale.out