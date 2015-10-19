all:libglsl.so test.out gputest.out example.out convert_data.out picture_treat.out gp_color_table.out gp_color_table_data_make.out color_extract.out 

ALL_INCLUESlibglsl.so= include//AllShader.h include//core/GLBmp.h include//core/GLDepthBuffer.h include//core/GLGrayBitmap.h include//core/GLRasterization.h include//fragment/GL_FragColor.h include//fragment/GL_FragPosition.h include//fragment/GL_FragTexcord.h include//fragment/GL_vPosition.h include//fragment/GLAbstractRasterizatedVarying.h include//fragment/GLLightFunction.h include//fragment/GLTexture2D.h include//fragment/GLWritePixels.h include//GL/debug.h include//GL/GLAutoFbo.h include//GL/GLAutoProgram.h include//GL/GLBasicObjectCreator.h include//GL/GLBezier.h include//GL/GLBiCubicCurveObj.h include//GL/GLBicubicWork.h include//GL/GLBitmapWork.h include//GL/GLBitmapWorkFactory.h include//GL/GLCamera.h include//GL/GLContext.h include//GL/GLCurveObject.h include//GL/GLCurveObjectFactory.h include//GL/GLDrawWork.h include//GL/GLFilterWork.h include//GL/GLFixScaleDrawWork.h include//GL/GLLightCurveObj.h include//GL/GLLightScene.h include//GL/GLMixWork.h include//GL/GLMultiPassDrawWork.h include//GL/GLMultiPassWork.h include//GL/GLObject.h include//GL/GLProgram.h include//GL/GLScene.h include//GL/GLSquareObjectCreator.h include//GL/GLTexture.h include//GL/GLTexture1Obj.h include//GL/GLTextureMultiObj.h include//GL/GLTextureWork.h include//GL/GLTransformer.h include//GL/GLTreeDrawWork.h include//GL/GLvboBuffer.h include//GL/GLvboBufferManager.h include//GL/GLWork.h include//GL/GLWorkHandler.h include//GL/GLWorkThread.h include//GL/head.h include//GL/IGLDrawWork.h include//interface/GLColor.h include//interface/head.h include//interface/IBasicVarying.h include//interface/IBitmap.h include//interface/IFragmentFunction.h include//interface/IRasterizatedVarying.h include//interface/IVarying.h include//interface/IVertexFunction.h include//math/AbstractPoint.h include//math/BasicFunctionDeter.h include//math/FormulaTree.h include//math/FunctionDeter.h include//math/GLCurveSurface.h include//math/GLMatrix4.h include//math/GLSphere.h include//math/GLVector.h include//math/IFunctionDeter.h include//package/basic.h include//package/DefaultFunctionTable.h include//package/fragment.h include//package/package.h include//package/vertex.h include//test/GLTest.h include//transform/GLBasicTransform.h include//transform/GLColorMap.h include//transform/GLFragPicture.h include//utils/ALClock.h include//utils/debug.h include//utils/GLAutoStorage.h include//utils/GLDefer.h include//utils/GLLock.h include//utils/GLMemoryPool.h include//utils/GLOnceWork.h include//utils/GLThread.h include//utils/GP_Clock.h include//utils/GPRandom.h include//utils/RefCount.h include//vertex/GL_Normal.h include//vertex/GL_position.h include//vertex/GL_texcord.h include//vertex/GLAbstractVarying.h include//vertex/GLVectorVarying.h include//AllShader.h include//core/GLBmp.h include//core/GLDepthBuffer.h include//core/GLGrayBitmap.h include//core/GLRasterization.h include//fragment/GL_FragColor.h include//fragment/GL_FragPosition.h include//fragment/GL_FragTexcord.h include//fragment/GL_vPosition.h include//fragment/GLAbstractRasterizatedVarying.h include//fragment/GLLightFunction.h include//fragment/GLTexture2D.h include//fragment/GLWritePixels.h include//GL/debug.h include//GL/GLAutoFbo.h include//GL/GLAutoProgram.h include//GL/GLBasicObjectCreator.h include//GL/GLBezier.h include//GL/GLBiCubicCurveObj.h include//GL/GLBicubicWork.h include//GL/GLBitmapWork.h include//GL/GLBitmapWorkFactory.h include//GL/GLCamera.h include//GL/GLContext.h include//GL/GLCurveObject.h include//GL/GLCurveObjectFactory.h include//GL/GLDrawWork.h include//GL/GLFilterWork.h include//GL/GLFixScaleDrawWork.h include//GL/GLLightCurveObj.h include//GL/GLLightScene.h include//GL/GLMixWork.h include//GL/GLMultiPassDrawWork.h include//GL/GLMultiPassWork.h include//GL/GLObject.h include//GL/GLProgram.h include//GL/GLScene.h include//GL/GLSquareObjectCreator.h include//GL/GLTexture.h include//GL/GLTexture1Obj.h include//GL/GLTextureMultiObj.h include//GL/GLTextureWork.h include//GL/GLTransformer.h include//GL/GLTreeDrawWork.h include//GL/GLvboBuffer.h include//GL/GLvboBufferManager.h include//GL/GLWork.h include//GL/GLWorkHandler.h include//GL/GLWorkThread.h include//GL/head.h include//GL/IGLDrawWork.h include//interface/GLColor.h include//interface/head.h include//interface/IBasicVarying.h include//interface/IBitmap.h include//interface/IFragmentFunction.h include//interface/IRasterizatedVarying.h include//interface/IVarying.h include//interface/IVertexFunction.h include//math/AbstractPoint.h include//math/BasicFunctionDeter.h include//math/FormulaTree.h include//math/FunctionDeter.h include//math/GLCurveSurface.h include//math/GLMatrix4.h include//math/GLSphere.h include//math/GLVector.h include//math/IFunctionDeter.h include//package/basic.h include//package/DefaultFunctionTable.h include//package/fragment.h include//package/package.h include//package/vertex.h include//test/GLTest.h include//transform/GLBasicTransform.h include//transform/GLColorMap.h include//transform/GLFragPicture.h include//utils/ALClock.h include//utils/debug.h include//utils/GLAutoStorage.h include//utils/GLDefer.h include//utils/GLLock.h include//utils/GLMemoryPool.h include//utils/GLOnceWork.h include//utils/GLThread.h include//utils/GP_Clock.h include//utils/GPRandom.h include//utils/RefCount.h include//vertex/GL_Normal.h include//vertex/GL_position.h include//vertex/GL_texcord.h include//vertex/GLAbstractVarying.h include//vertex/GLVectorVarying.h

libglsl.so:  build/src_core_GLBmp.o build/src_core_GLDepthBuffer.o build/src_core_GLGrayBitmap.o build/src_core_GLRasterization.o build/src_core_weightTable.o build/src_fragment_GLAbstractRasterizatedVarying.o build/src_fragment_GLLightFunction.o build/src_fragment_GLWritePixels.o build/src_fragment_texture2D.o build/src_GL_GLAutoFbo.o build/src_GL_GLAutoProgram.o build/src_GL_GLBezier.o build/src_GL_GLBiCubicCurveObj.o build/src_GL_GLBicubicWork.o build/src_GL_GLBitmapWork.o build/src_GL_GLBitmapWorkFactory.o build/src_GL_GLCamera.o build/src_GL_GLCurveObject.o build/src_GL_GLCurveObjectFactory.o build/src_GL_GLDrawWork.o build/src_GL_GLFilterWork.o build/src_GL_GLFixScaleDrawWork.o build/src_GL_GLFraction.o build/src_GL_GLLightCurveObject.o build/src_GL_GLLightScene.o build/src_GL_GLMixWork.o build/src_GL_GLMultiPassDrawWork.o build/src_GL_GLMultiPassWork.o build/src_GL_GLProgram.o build/src_GL_GLScene.o build/src_GL_GLSquareObjectCreator.o build/src_GL_GLTexture.o build/src_GL_GLTexture1Obj.o build/src_GL_GLTextureWork.o build/src_GL_GLTreeDrawWork.o build/src_GL_GLvboBuffer.o build/src_GL_GLvboBufferManager.o build/src_GL_GLWorkThread.o build/src_GL_IGLDrawWork.o build/src_math_AbstractPoint.o build/src_math_BasicFunctionDeter.o build/src_math_FormulaTree.o build/src_math_GLMatrix4.o build/src_math_GLSphere.o build/src_math_GLVector.o build/src_package_DefaultFunctionTable.o build/src_package_fragment.o build/src_package_GPPackage.o build/src_package_GPTypes.o build/src_platform_GLContext.o build/src_platform_GLLock.o build/src_transform_ColorMover.o build/src_transform_GLBasicTransform.o build/src_transform_GLColorMap.o build/src_transform_GLFragPicture.o build/src_transform_SceneNewton.o build/src_utils_GLOnceWork.o build/src_utils_GLThread.o build/src_utils_GP_Clock.o build/src_utils_GPRandom.o build/src_vertex_GL_Normal.o build/src_vertex_GL_position.o build/src_vertex_GLAbstractVarying.o build/src_vertex_GLVectorVarying.o build/glsl_AllShader.o build/src_utils_debug.o build/src_utils_GLMemoryPool.o 
	g++ -std=c++11  -O3 -fPIC  --shared   ./third_party/FreeImage/libfreeimage.a -framework OpenGL -framework GLUT -framework AGL -o libglsl.so  build/src_core_GLBmp.o build/src_core_GLDepthBuffer.o build/src_core_GLGrayBitmap.o build/src_core_GLRasterization.o build/src_core_weightTable.o build/src_fragment_GLAbstractRasterizatedVarying.o build/src_fragment_GLLightFunction.o build/src_fragment_GLWritePixels.o build/src_fragment_texture2D.o build/src_GL_GLAutoFbo.o build/src_GL_GLAutoProgram.o build/src_GL_GLBezier.o build/src_GL_GLBiCubicCurveObj.o build/src_GL_GLBicubicWork.o build/src_GL_GLBitmapWork.o build/src_GL_GLBitmapWorkFactory.o build/src_GL_GLCamera.o build/src_GL_GLCurveObject.o build/src_GL_GLCurveObjectFactory.o build/src_GL_GLDrawWork.o build/src_GL_GLFilterWork.o build/src_GL_GLFixScaleDrawWork.o build/src_GL_GLFraction.o build/src_GL_GLLightCurveObject.o build/src_GL_GLLightScene.o build/src_GL_GLMixWork.o build/src_GL_GLMultiPassDrawWork.o build/src_GL_GLMultiPassWork.o build/src_GL_GLProgram.o build/src_GL_GLScene.o build/src_GL_GLSquareObjectCreator.o build/src_GL_GLTexture.o build/src_GL_GLTexture1Obj.o build/src_GL_GLTextureWork.o build/src_GL_GLTreeDrawWork.o build/src_GL_GLvboBuffer.o build/src_GL_GLvboBufferManager.o build/src_GL_GLWorkThread.o build/src_GL_IGLDrawWork.o build/src_math_AbstractPoint.o build/src_math_BasicFunctionDeter.o build/src_math_FormulaTree.o build/src_math_GLMatrix4.o build/src_math_GLSphere.o build/src_math_GLVector.o build/src_package_DefaultFunctionTable.o build/src_package_fragment.o build/src_package_GPPackage.o build/src_package_GPTypes.o build/src_platform_GLContext.o build/src_platform_GLLock.o build/src_transform_ColorMover.o build/src_transform_GLBasicTransform.o build/src_transform_GLColorMap.o build/src_transform_GLFragPicture.o build/src_transform_SceneNewton.o build/src_utils_GLOnceWork.o build/src_utils_GLThread.o build/src_utils_GP_Clock.o build/src_utils_GPRandom.o build/src_vertex_GL_Normal.o build/src_vertex_GL_position.o build/src_vertex_GLAbstractVarying.o build/src_vertex_GLVectorVarying.o build/glsl_AllShader.o build/src_utils_debug.o build/src_utils_GLMemoryPool.o ${SELF_VARIABLES}
build/src_core_GLBmp.o : src/core/GLBmp.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_core_GLBmp.o -c src/core/GLBmp.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_core_GLDepthBuffer.o : src/core/GLDepthBuffer.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_core_GLDepthBuffer.o -c src/core/GLDepthBuffer.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_core_GLGrayBitmap.o : src/core/GLGrayBitmap.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_core_GLGrayBitmap.o -c src/core/GLGrayBitmap.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_core_GLRasterization.o : src/core/GLRasterization.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_core_GLRasterization.o -c src/core/GLRasterization.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_core_weightTable.o : src/core/weightTable.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_core_weightTable.o -c src/core/weightTable.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_fragment_GLAbstractRasterizatedVarying.o : src/fragment/GLAbstractRasterizatedVarying.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_fragment_GLAbstractRasterizatedVarying.o -c src/fragment/GLAbstractRasterizatedVarying.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_fragment_GLLightFunction.o : src/fragment/GLLightFunction.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_fragment_GLLightFunction.o -c src/fragment/GLLightFunction.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_fragment_GLWritePixels.o : src/fragment/GLWritePixels.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_fragment_GLWritePixels.o -c src/fragment/GLWritePixels.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_fragment_texture2D.o : src/fragment/texture2D.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_fragment_texture2D.o -c src/fragment/texture2D.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLAutoFbo.o : src/GL/GLAutoFbo.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLAutoFbo.o -c src/GL/GLAutoFbo.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLAutoProgram.o : src/GL/GLAutoProgram.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLAutoProgram.o -c src/GL/GLAutoProgram.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLBezier.o : src/GL/GLBezier.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLBezier.o -c src/GL/GLBezier.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLBiCubicCurveObj.o : src/GL/GLBiCubicCurveObj.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLBiCubicCurveObj.o -c src/GL/GLBiCubicCurveObj.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLBicubicWork.o : src/GL/GLBicubicWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLBicubicWork.o -c src/GL/GLBicubicWork.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLBitmapWork.o : src/GL/GLBitmapWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLBitmapWork.o -c src/GL/GLBitmapWork.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLBitmapWorkFactory.o : src/GL/GLBitmapWorkFactory.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLBitmapWorkFactory.o -c src/GL/GLBitmapWorkFactory.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLCamera.o : src/GL/GLCamera.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLCamera.o -c src/GL/GLCamera.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLCurveObject.o : src/GL/GLCurveObject.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLCurveObject.o -c src/GL/GLCurveObject.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLCurveObjectFactory.o : src/GL/GLCurveObjectFactory.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLCurveObjectFactory.o -c src/GL/GLCurveObjectFactory.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLDrawWork.o : src/GL/GLDrawWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLDrawWork.o -c src/GL/GLDrawWork.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLFilterWork.o : src/GL/GLFilterWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLFilterWork.o -c src/GL/GLFilterWork.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLFixScaleDrawWork.o : src/GL/GLFixScaleDrawWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLFixScaleDrawWork.o -c src/GL/GLFixScaleDrawWork.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLFraction.o : src/GL/GLFraction.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLFraction.o -c src/GL/GLFraction.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLLightCurveObject.o : src/GL/GLLightCurveObject.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLLightCurveObject.o -c src/GL/GLLightCurveObject.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLLightScene.o : src/GL/GLLightScene.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLLightScene.o -c src/GL/GLLightScene.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLMixWork.o : src/GL/GLMixWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLMixWork.o -c src/GL/GLMixWork.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLMultiPassDrawWork.o : src/GL/GLMultiPassDrawWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLMultiPassDrawWork.o -c src/GL/GLMultiPassDrawWork.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLMultiPassWork.o : src/GL/GLMultiPassWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLMultiPassWork.o -c src/GL/GLMultiPassWork.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLProgram.o : src/GL/GLProgram.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLProgram.o -c src/GL/GLProgram.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLScene.o : src/GL/GLScene.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLScene.o -c src/GL/GLScene.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLSquareObjectCreator.o : src/GL/GLSquareObjectCreator.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLSquareObjectCreator.o -c src/GL/GLSquareObjectCreator.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLTexture.o : src/GL/GLTexture.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLTexture.o -c src/GL/GLTexture.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLTexture1Obj.o : src/GL/GLTexture1Obj.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLTexture1Obj.o -c src/GL/GLTexture1Obj.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLTextureWork.o : src/GL/GLTextureWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLTextureWork.o -c src/GL/GLTextureWork.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLTreeDrawWork.o : src/GL/GLTreeDrawWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLTreeDrawWork.o -c src/GL/GLTreeDrawWork.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLvboBuffer.o : src/GL/GLvboBuffer.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLvboBuffer.o -c src/GL/GLvboBuffer.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLvboBufferManager.o : src/GL/GLvboBufferManager.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLvboBufferManager.o -c src/GL/GLvboBufferManager.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_GLWorkThread.o : src/GL/GLWorkThread.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_GLWorkThread.o -c src/GL/GLWorkThread.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_GL_IGLDrawWork.o : src/GL/IGLDrawWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_GL_IGLDrawWork.o -c src/GL/IGLDrawWork.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_math_AbstractPoint.o : src/math/AbstractPoint.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_math_AbstractPoint.o -c src/math/AbstractPoint.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_math_BasicFunctionDeter.o : src/math/BasicFunctionDeter.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_math_BasicFunctionDeter.o -c src/math/BasicFunctionDeter.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_math_FormulaTree.o : src/math/FormulaTree.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_math_FormulaTree.o -c src/math/FormulaTree.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_math_GLMatrix4.o : src/math/GLMatrix4.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_math_GLMatrix4.o -c src/math/GLMatrix4.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_math_GLSphere.o : src/math/GLSphere.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_math_GLSphere.o -c src/math/GLSphere.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_math_GLVector.o : src/math/GLVector.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_math_GLVector.o -c src/math/GLVector.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_package_DefaultFunctionTable.o : src/package/DefaultFunctionTable.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_package_DefaultFunctionTable.o -c src/package/DefaultFunctionTable.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_package_fragment.o : src/package/fragment.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_package_fragment.o -c src/package/fragment.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_package_GPPackage.o : src/package/GPPackage.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_package_GPPackage.o -c src/package/GPPackage.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_package_GPTypes.o : src/package/GPTypes.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_package_GPTypes.o -c src/package/GPTypes.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_platform_GLContext.o : src/platform/GLContext.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_platform_GLContext.o -c src/platform/GLContext.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_platform_GLLock.o : src/platform/GLLock.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_platform_GLLock.o -c src/platform/GLLock.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_transform_ColorMover.o : src/transform/ColorMover.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_transform_ColorMover.o -c src/transform/ColorMover.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_transform_GLBasicTransform.o : src/transform/GLBasicTransform.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_transform_GLBasicTransform.o -c src/transform/GLBasicTransform.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_transform_GLColorMap.o : src/transform/GLColorMap.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_transform_GLColorMap.o -c src/transform/GLColorMap.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_transform_GLFragPicture.o : src/transform/GLFragPicture.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_transform_GLFragPicture.o -c src/transform/GLFragPicture.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_transform_SceneNewton.o : src/transform/SceneNewton.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_transform_SceneNewton.o -c src/transform/SceneNewton.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_utils_GLOnceWork.o : src/utils/GLOnceWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_utils_GLOnceWork.o -c src/utils/GLOnceWork.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_utils_GLThread.o : src/utils/GLThread.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_utils_GLThread.o -c src/utils/GLThread.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_utils_GP_Clock.o : src/utils/GP_Clock.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_utils_GP_Clock.o -c src/utils/GP_Clock.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_utils_GPRandom.o : src/utils/GPRandom.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_utils_GPRandom.o -c src/utils/GPRandom.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_vertex_GL_Normal.o : src/vertex/GL_Normal.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_vertex_GL_Normal.o -c src/vertex/GL_Normal.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_vertex_GL_position.o : src/vertex/GL_position.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_vertex_GL_position.o -c src/vertex/GL_position.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_vertex_GLAbstractVarying.o : src/vertex/GLAbstractVarying.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_vertex_GLAbstractVarying.o -c src/vertex/GLAbstractVarying.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_vertex_GLVectorVarying.o : src/vertex/GLVectorVarying.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/src_vertex_GLVectorVarying.o -c src/vertex/GLVectorVarying.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/glsl_AllShader.o : glsl/AllShader.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -std=c++11 -O3 -fPIC -o build/glsl_AllShader.o -c glsl/AllShader.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_utils_debug.o : src/utils/debug.c   ${ALL_INCLUESlibglsl.so}
	gcc -std=c11 -O3 -fPIC -o build/src_utils_debug.o -c src/utils/debug.c -Iinclude -I../Genetic-Program-Frame/include/
  
build/src_utils_GLMemoryPool.o : src/utils/GLMemoryPool.c   ${ALL_INCLUESlibglsl.so}
	gcc -std=c11 -O3 -fPIC -o build/src_utils_GLMemoryPool.o -c src/utils/GLMemoryPool.c -Iinclude -I../Genetic-Program-Frame/include/
  

ALL_INCLUEStest.out= include//AllShader.h include//core/GLBmp.h include//core/GLDepthBuffer.h include//core/GLGrayBitmap.h include//core/GLRasterization.h include//fragment/GL_FragColor.h include//fragment/GL_FragPosition.h include//fragment/GL_FragTexcord.h include//fragment/GL_vPosition.h include//fragment/GLAbstractRasterizatedVarying.h include//fragment/GLLightFunction.h include//fragment/GLTexture2D.h include//fragment/GLWritePixels.h include//GL/debug.h include//GL/GLAutoFbo.h include//GL/GLAutoProgram.h include//GL/GLBasicObjectCreator.h include//GL/GLBezier.h include//GL/GLBiCubicCurveObj.h include//GL/GLBicubicWork.h include//GL/GLBitmapWork.h include//GL/GLBitmapWorkFactory.h include//GL/GLCamera.h include//GL/GLContext.h include//GL/GLCurveObject.h include//GL/GLCurveObjectFactory.h include//GL/GLDrawWork.h include//GL/GLFilterWork.h include//GL/GLFixScaleDrawWork.h include//GL/GLLightCurveObj.h include//GL/GLLightScene.h include//GL/GLMixWork.h include//GL/GLMultiPassDrawWork.h include//GL/GLMultiPassWork.h include//GL/GLObject.h include//GL/GLProgram.h include//GL/GLScene.h include//GL/GLSquareObjectCreator.h include//GL/GLTexture.h include//GL/GLTexture1Obj.h include//GL/GLTextureMultiObj.h include//GL/GLTextureWork.h include//GL/GLTransformer.h include//GL/GLTreeDrawWork.h include//GL/GLvboBuffer.h include//GL/GLvboBufferManager.h include//GL/GLWork.h include//GL/GLWorkHandler.h include//GL/GLWorkThread.h include//GL/head.h include//GL/IGLDrawWork.h include//interface/GLColor.h include//interface/head.h include//interface/IBasicVarying.h include//interface/IBitmap.h include//interface/IFragmentFunction.h include//interface/IRasterizatedVarying.h include//interface/IVarying.h include//interface/IVertexFunction.h include//math/AbstractPoint.h include//math/BasicFunctionDeter.h include//math/FormulaTree.h include//math/FunctionDeter.h include//math/GLCurveSurface.h include//math/GLMatrix4.h include//math/GLSphere.h include//math/GLVector.h include//math/IFunctionDeter.h include//package/basic.h include//package/DefaultFunctionTable.h include//package/fragment.h include//package/package.h include//package/vertex.h include//test/GLTest.h include//transform/GLBasicTransform.h include//transform/GLColorMap.h include//transform/GLFragPicture.h include//utils/ALClock.h include//utils/debug.h include//utils/GLAutoStorage.h include//utils/GLDefer.h include//utils/GLLock.h include//utils/GLMemoryPool.h include//utils/GLOnceWork.h include//utils/GLThread.h include//utils/GP_Clock.h include//utils/GPRandom.h include//utils/RefCount.h include//vertex/GL_Normal.h include//vertex/GL_position.h include//vertex/GL_texcord.h include//vertex/GLAbstractVarying.h include//vertex/GLVectorVarying.h

test.out:  build/test_GLBmpTest.o build/test_GLColorMapTest.o build/test_GLFragTest.o build/test_GLGrayTest.o build/test_GLProjectionTest.o build/test_GLRasterBasic.o build/test_GLRotateTest.o build/test_GLSingleLightTest.o build/test_GLTest.o build/test_main.o libglsl.so
	g++ -std=c++11  -O3 -fPIC   ./libglsl.so -o test.out  build/test_GLBmpTest.o build/test_GLColorMapTest.o build/test_GLFragTest.o build/test_GLGrayTest.o build/test_GLProjectionTest.o build/test_GLRasterBasic.o build/test_GLRotateTest.o build/test_GLSingleLightTest.o build/test_GLTest.o build/test_main.o ${SELF_VARIABLES}
build/test_GLBmpTest.o : test/GLBmpTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -fPIC -o build/test_GLBmpTest.o -c test/GLBmpTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/test_GLColorMapTest.o : test/GLColorMapTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -fPIC -o build/test_GLColorMapTest.o -c test/GLColorMapTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/test_GLFragTest.o : test/GLFragTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -fPIC -o build/test_GLFragTest.o -c test/GLFragTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/test_GLGrayTest.o : test/GLGrayTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -fPIC -o build/test_GLGrayTest.o -c test/GLGrayTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/test_GLProjectionTest.o : test/GLProjectionTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -fPIC -o build/test_GLProjectionTest.o -c test/GLProjectionTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/test_GLRasterBasic.o : test/GLRasterBasic.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -fPIC -o build/test_GLRasterBasic.o -c test/GLRasterBasic.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/test_GLRotateTest.o : test/GLRotateTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -fPIC -o build/test_GLRotateTest.o -c test/GLRotateTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/test_GLSingleLightTest.o : test/GLSingleLightTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -fPIC -o build/test_GLSingleLightTest.o -c test/GLSingleLightTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/test_GLTest.o : test/GLTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -fPIC -o build/test_GLTest.o -c test/GLTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/test_main.o : test/main.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -fPIC -o build/test_main.o -c test/main.cpp -Iinclude -I../Genetic-Program-Frame/include/
  

ALL_INCLUESgputest.out= include//AllShader.h include//core/GLBmp.h include//core/GLDepthBuffer.h include//core/GLGrayBitmap.h include//core/GLRasterization.h include//fragment/GL_FragColor.h include//fragment/GL_FragPosition.h include//fragment/GL_FragTexcord.h include//fragment/GL_vPosition.h include//fragment/GLAbstractRasterizatedVarying.h include//fragment/GLLightFunction.h include//fragment/GLTexture2D.h include//fragment/GLWritePixels.h include//GL/debug.h include//GL/GLAutoFbo.h include//GL/GLAutoProgram.h include//GL/GLBasicObjectCreator.h include//GL/GLBezier.h include//GL/GLBiCubicCurveObj.h include//GL/GLBicubicWork.h include//GL/GLBitmapWork.h include//GL/GLBitmapWorkFactory.h include//GL/GLCamera.h include//GL/GLContext.h include//GL/GLCurveObject.h include//GL/GLCurveObjectFactory.h include//GL/GLDrawWork.h include//GL/GLFilterWork.h include//GL/GLFixScaleDrawWork.h include//GL/GLLightCurveObj.h include//GL/GLLightScene.h include//GL/GLMixWork.h include//GL/GLMultiPassDrawWork.h include//GL/GLMultiPassWork.h include//GL/GLObject.h include//GL/GLProgram.h include//GL/GLScene.h include//GL/GLSquareObjectCreator.h include//GL/GLTexture.h include//GL/GLTexture1Obj.h include//GL/GLTextureMultiObj.h include//GL/GLTextureWork.h include//GL/GLTransformer.h include//GL/GLTreeDrawWork.h include//GL/GLvboBuffer.h include//GL/GLvboBufferManager.h include//GL/GLWork.h include//GL/GLWorkHandler.h include//GL/GLWorkThread.h include//GL/head.h include//GL/IGLDrawWork.h include//interface/GLColor.h include//interface/head.h include//interface/IBasicVarying.h include//interface/IBitmap.h include//interface/IFragmentFunction.h include//interface/IRasterizatedVarying.h include//interface/IVarying.h include//interface/IVertexFunction.h include//math/AbstractPoint.h include//math/BasicFunctionDeter.h include//math/FormulaTree.h include//math/FunctionDeter.h include//math/GLCurveSurface.h include//math/GLMatrix4.h include//math/GLSphere.h include//math/GLVector.h include//math/IFunctionDeter.h include//package/basic.h include//package/DefaultFunctionTable.h include//package/fragment.h include//package/package.h include//package/vertex.h include//test/GLTest.h include//transform/GLBasicTransform.h include//transform/GLColorMap.h include//transform/GLFragPicture.h include//utils/ALClock.h include//utils/debug.h include//utils/GLAutoStorage.h include//utils/GLDefer.h include//utils/GLLock.h include//utils/GLMemoryPool.h include//utils/GLOnceWork.h include//utils/GLThread.h include//utils/GP_Clock.h include//utils/GPRandom.h include//utils/RefCount.h include//vertex/GL_Normal.h include//vertex/GL_position.h include//vertex/GL_texcord.h include//vertex/GLAbstractVarying.h include//vertex/GLVectorVarying.h

gputest.out:  build/gltest_GLBitmapWorkTest.o build/gltest_GLCubicTest.o build/gltest_GLFactoryTest.o build/gltest_GLFilterTest.o build/gltest_GLFractionByGLTest.o build/gltest_GLMixFractionTest.o build/gltest_GLScalePSNRTest.o build/gltest_GLTest.o build/gltest_GLWorkThreadTest.o build/gltest_opengltest_main.o libglsl.so
	g++ -std=c++11  -O3 -fPIC   ./libglsl.so -o gputest.out  build/gltest_GLBitmapWorkTest.o build/gltest_GLCubicTest.o build/gltest_GLFactoryTest.o build/gltest_GLFilterTest.o build/gltest_GLFractionByGLTest.o build/gltest_GLMixFractionTest.o build/gltest_GLScalePSNRTest.o build/gltest_GLTest.o build/gltest_GLWorkThreadTest.o build/gltest_opengltest_main.o ${SELF_VARIABLES}
build/gltest_GLBitmapWorkTest.o : gltest/GLBitmapWorkTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -fPIC -o build/gltest_GLBitmapWorkTest.o -c gltest/GLBitmapWorkTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/gltest_GLCubicTest.o : gltest/GLCubicTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -fPIC -o build/gltest_GLCubicTest.o -c gltest/GLCubicTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/gltest_GLFactoryTest.o : gltest/GLFactoryTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -fPIC -o build/gltest_GLFactoryTest.o -c gltest/GLFactoryTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/gltest_GLFilterTest.o : gltest/GLFilterTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -fPIC -o build/gltest_GLFilterTest.o -c gltest/GLFilterTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/gltest_GLFractionByGLTest.o : gltest/GLFractionByGLTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -fPIC -o build/gltest_GLFractionByGLTest.o -c gltest/GLFractionByGLTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/gltest_GLMixFractionTest.o : gltest/GLMixFractionTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -fPIC -o build/gltest_GLMixFractionTest.o -c gltest/GLMixFractionTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/gltest_GLScalePSNRTest.o : gltest/GLScalePSNRTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -fPIC -o build/gltest_GLScalePSNRTest.o -c gltest/GLScalePSNRTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/gltest_GLTest.o : gltest/GLTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -fPIC -o build/gltest_GLTest.o -c gltest/GLTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/gltest_GLWorkThreadTest.o : gltest/GLWorkThreadTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -fPIC -o build/gltest_GLWorkThreadTest.o -c gltest/GLWorkThreadTest.cpp -Iinclude -I../Genetic-Program-Frame/include/
  
build/gltest_opengltest_main.o : gltest/opengltest_main.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -std=c++11 -O3 -fPIC -o build/gltest_opengltest_main.o -c gltest/opengltest_main.cpp -Iinclude -I../Genetic-Program-Frame/include/
  

ALL_INCLUESexample.out= include//AllShader.h include//core/GLBmp.h include//core/GLDepthBuffer.h include//core/GLGrayBitmap.h include//core/GLRasterization.h include//fragment/GL_FragColor.h include//fragment/GL_FragPosition.h include//fragment/GL_FragTexcord.h include//fragment/GL_vPosition.h include//fragment/GLAbstractRasterizatedVarying.h include//fragment/GLLightFunction.h include//fragment/GLTexture2D.h include//fragment/GLWritePixels.h include//GL/debug.h include//GL/GLAutoFbo.h include//GL/GLAutoProgram.h include//GL/GLBasicObjectCreator.h include//GL/GLBezier.h include//GL/GLBiCubicCurveObj.h include//GL/GLBicubicWork.h include//GL/GLBitmapWork.h include//GL/GLBitmapWorkFactory.h include//GL/GLCamera.h include//GL/GLContext.h include//GL/GLCurveObject.h include//GL/GLCurveObjectFactory.h include//GL/GLDrawWork.h include//GL/GLFilterWork.h include//GL/GLFixScaleDrawWork.h include//GL/GLLightCurveObj.h include//GL/GLLightScene.h include//GL/GLMixWork.h include//GL/GLMultiPassDrawWork.h include//GL/GLMultiPassWork.h include//GL/GLObject.h include//GL/GLProgram.h include//GL/GLScene.h include//GL/GLSquareObjectCreator.h include//GL/GLTexture.h include//GL/GLTexture1Obj.h include//GL/GLTextureMultiObj.h include//GL/GLTextureWork.h include//GL/GLTransformer.h include//GL/GLTreeDrawWork.h include//GL/GLvboBuffer.h include//GL/GLvboBufferManager.h include//GL/GLWork.h include//GL/GLWorkHandler.h include//GL/GLWorkThread.h include//GL/head.h include//GL/IGLDrawWork.h include//interface/GLColor.h include//interface/head.h include//interface/IBasicVarying.h include//interface/IBitmap.h include//interface/IFragmentFunction.h include//interface/IRasterizatedVarying.h include//interface/IVarying.h include//interface/IVertexFunction.h include//math/AbstractPoint.h include//math/BasicFunctionDeter.h include//math/FormulaTree.h include//math/FunctionDeter.h include//math/GLCurveSurface.h include//math/GLMatrix4.h include//math/GLSphere.h include//math/GLVector.h include//math/IFunctionDeter.h include//package/basic.h include//package/DefaultFunctionTable.h include//package/fragment.h include//package/package.h include//package/vertex.h include//test/GLTest.h include//transform/GLBasicTransform.h include//transform/GLColorMap.h include//transform/GLFragPicture.h include//utils/ALClock.h include//utils/debug.h include//utils/GLAutoStorage.h include//utils/GLDefer.h include//utils/GLLock.h include//utils/GLMemoryPool.h include//utils/GLOnceWork.h include//utils/GLThread.h include//utils/GP_Clock.h include//utils/GPRandom.h include//utils/RefCount.h include//vertex/GL_Normal.h include//vertex/GL_position.h include//vertex/GL_texcord.h include//vertex/GLAbstractVarying.h include//vertex/GLVectorVarying.h

example.out:  build/example_main.o libglsl.so
	g++ -std=c++11  -O3 -fPIC   ./libglsl.so -o example.out  build/example_main.o ${SELF_VARIABLES}
build/example_main.o : example/main.cpp libglsl.so  ${ALL_INCLUESexample.out}
	g++ -std=c++11 -O3 -fPIC -o build/example_main.o -c example/main.cpp -Iinclude -I../Genetic-Program-Frame/include/
  

ALL_INCLUESconvert_data.out=

convert_data.out:  build/convert_data.o libglsl.so
	g++ -std=c++11  -O3 -fPIC   ./libglsl.so -o convert_data.out  build/convert_data.o ${SELF_VARIABLES}
build/convert_data.o : convert_data.cpp libglsl.so  ${ALL_INCLUESconvert_data.out}
	g++ -std=c++11 -O3 -fPIC -o build/convert_data.o -c convert_data.cpp -Iinclude -I../Genetic-Program-Frame/include/
  

ALL_INCLUESpicture_treat.out=

picture_treat.out:  build/picture_treat.o libglsl.so
	g++ -std=c++11  -O3 -fPIC   ./libglsl.so -o picture_treat.out  build/picture_treat.o ${SELF_VARIABLES}
build/picture_treat.o : picture_treat.cpp libglsl.so  ${ALL_INCLUESpicture_treat.out}
	g++ -std=c++11 -O3 -fPIC -o build/picture_treat.o -c picture_treat.cpp -Iinclude -I../Genetic-Program-Frame/include/
  

ALL_INCLUESgp_color_table.out=

gp_color_table.out:  build/gp_color_table.o libglsl.so
	g++ -std=c++11  -O3 -fPIC   ./libglsl.so ./libGP.so -o gp_color_table.out  build/gp_color_table.o ${SELF_VARIABLES}
build/gp_color_table.o : gp_color_table.cpp libglsl.so  ${ALL_INCLUESgp_color_table.out}
	g++ -std=c++11 -O3 -fPIC -o build/gp_color_table.o -c gp_color_table.cpp -Iinclude -I../Genetic-Program-Frame/include/
  

ALL_INCLUESgp_color_table_data_make.out=

gp_color_table_data_make.out:  build/gp_color_table_data_make.o libglsl.so
	g++ -std=c++11  -O3 -fPIC   ./libglsl.so -o gp_color_table_data_make.out  build/gp_color_table_data_make.o ${SELF_VARIABLES}
build/gp_color_table_data_make.o : gp_color_table_data_make.cpp libglsl.so  ${ALL_INCLUESgp_color_table_data_make.out}
	g++ -std=c++11 -O3 -fPIC -o build/gp_color_table_data_make.o -c gp_color_table_data_make.cpp -Iinclude -I../Genetic-Program-Frame/include/
  

ALL_INCLUEScolor_extract.out=

color_extract.out:  build/color_extract.o libglsl.so
	g++ -std=c++11  -O3 -fPIC   ./libglsl.so -o color_extract.out  build/color_extract.o ${SELF_VARIABLES}
build/color_extract.o : color_extract.cpp libglsl.so  ${ALL_INCLUEScolor_extract.out}
	g++ -std=c++11 -O3 -fPIC -o build/color_extract.o -c color_extract.cpp -Iinclude -I../Genetic-Program-Frame/include/
  

clean:
	rm build/*.o
	rm libglsl.so
	rm test.out
	rm gputest.out
	rm example.out
	rm convert_data.out
	rm picture_treat.out
	rm gp_color_table.out
	rm gp_color_table_data_make.out
	rm color_extract.out