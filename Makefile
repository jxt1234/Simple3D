all:libglsl.so test.out gputest.out display.out 

ALL_INCLUESlibglsl.so= include/test/GLTest.h include/math/GLVector.h include/math/GLMatrix4.h include/math/GLSphere.h include/math/GLCurveSurface.h include/fragment/GL_FragTexcord.h include/fragment/GLAbstractRasterizatedVarying.h include/fragment/GL_FragPosition.h include/fragment/GLLightFunction.h include/fragment/GL_vPosition.h include/fragment/GLWritePixels.h include/fragment/GL_FragColor.h include/fragment/GLTexture2D.h include/GL/GLBicubicWork.h include/GL/GLBasicObjectCreator.h include/GL/GLMultiPassWork.h include/GL/GLTextureMultiObj.h include/GL/GLTransformer.h include/GL/GLAutoFbo.h include/GL/GLvboBuffer.h include/GL/GLAutoProgram.h include/GL/GLSquareObjectCreator.h include/GL/GLProgram.h include/GL/GLWork.h include/GL/GLTexture.h include/GL/GLBitmapWorkFactory.h include/GL/GLLightScene.h include/GL/GLBezier.h include/GL/debug.h include/GL/GLCamera.h include/GL/GLWorkThread.h include/GL/GLWorkHandler.h include/GL/GLBitmapWork.h include/GL/GLObject.h include/GL/GLCurveObject.h include/GL/GLTexture1Obj.h include/GL/GLFilterWork.h include/GL/head.h include/GL/GLScene.h include/package/vertex.h include/package/basic.h include/package/fragment.h include/package/package.h include/interface/IVertexFunction.h include/interface/IBitmap.h include/interface/IBasicVarying.h include/interface/GLColor.h include/interface/IFragmentFunction.h include/interface/IVarying.h include/interface/head.h include/interface/IRasterizatedVarying.h include/core/GLBmp.h include/core/GLDepthBuffer.h include/core/GLRasterization.h include/transform/GLFragPicture.h include/transform/GLBasicTransform.h include/vertex/GLVectorVarying.h include/vertex/GL_texcord.h include/vertex/GLAbstractVarying.h include/vertex/GL_Normal.h include/vertex/GL_position.h include/utils/RefCount.h include/utils/GLLock.h include/utils/debug.h include/utils/GP_Clock.h include/utils/GLThread.h include/utils/GPRandom.h

libglsl.so:  build/src_math_GLMatrix.o build/src_math_GLVector.o build/src_math_GLSphere.o build/src_fragment_GLWritePixels.o build/src_fragment_GLLightFunction.o build/src_fragment_GLAbstractRasterizatedVarying.o build/src_fragment_texture2D.o build/src_GL_GLTexture1Obj.o build/src_GL_GLCamera.o build/src_GL_GLBicubicWork.o build/src_GL_GLScene.o build/src_GL_GLFraction.o build/src_GL_GLCurveObject.o build/src_GL_GLFilterWork.o build/src_GL_GLBezier.o build/src_GL_GLProgram.o build/src_GL_GLBitmapWorkFactory.o build/src_GL_GLLightScene.o build/src_GL_GLAutoProgram.o build/src_GL_GLTexture.o build/src_GL_GLSquareObjectCreator.o build/src_GL_GLMultiPassWork.o build/src_GL_GLvboBuffer.o build/src_GL_GLBitmapWork.o build/src_GL_GLAutoFbo.o build/src_GL_GLWorkThread.o build/src_package_fragment.o build/src_platform_GLLock.o build/src_core_weightTable.o build/src_core_GLBmp.o build/src_core_GLRasterization.o build/src_core_GLDepthBuffer.o build/src_transform_GLBasicTransform.o build/src_transform_ColorMover.o build/src_transform_SceneNewton.o build/src_transform_GLFragPicture.o build/src_vertex_GLAbstractVarying.o build/src_vertex_GL_position.o build/src_vertex_GL_Normal.o build/src_vertex_GLVectorVarying.o build/src_utils_GP_Clock.o build/src_utils_GPRandom.o build/src_utils_GLThread.o build/src_utils_debug.o 
	g++  -O3 -fPIC --share  -o libglsl.so  build/src_math_GLMatrix.o build/src_math_GLVector.o build/src_math_GLSphere.o build/src_fragment_GLWritePixels.o build/src_fragment_GLLightFunction.o build/src_fragment_GLAbstractRasterizatedVarying.o build/src_fragment_texture2D.o build/src_GL_GLTexture1Obj.o build/src_GL_GLCamera.o build/src_GL_GLBicubicWork.o build/src_GL_GLScene.o build/src_GL_GLFraction.o build/src_GL_GLCurveObject.o build/src_GL_GLFilterWork.o build/src_GL_GLBezier.o build/src_GL_GLProgram.o build/src_GL_GLBitmapWorkFactory.o build/src_GL_GLLightScene.o build/src_GL_GLAutoProgram.o build/src_GL_GLTexture.o build/src_GL_GLSquareObjectCreator.o build/src_GL_GLMultiPassWork.o build/src_GL_GLvboBuffer.o build/src_GL_GLBitmapWork.o build/src_GL_GLAutoFbo.o build/src_GL_GLWorkThread.o build/src_package_fragment.o build/src_platform_GLLock.o build/src_core_weightTable.o build/src_core_GLBmp.o build/src_core_GLRasterization.o build/src_core_GLDepthBuffer.o build/src_transform_GLBasicTransform.o build/src_transform_ColorMover.o build/src_transform_SceneNewton.o build/src_transform_GLFragPicture.o build/src_vertex_GLAbstractVarying.o build/src_vertex_GL_position.o build/src_vertex_GL_Normal.o build/src_vertex_GLVectorVarying.o build/src_utils_GP_Clock.o build/src_utils_GPRandom.o build/src_utils_GLThread.o build/src_utils_debug.o  -lfreeimage  ${SELF_VARIABLES}
build/src_math_GLMatrix.o : src/math/GLMatrix.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_math_GLMatrix.o -c src/math/GLMatrix.cpp -Iinclude 
build/src_math_GLVector.o : src/math/GLVector.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_math_GLVector.o -c src/math/GLVector.cpp -Iinclude 
build/src_math_GLSphere.o : src/math/GLSphere.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_math_GLSphere.o -c src/math/GLSphere.cpp -Iinclude 
build/src_fragment_GLWritePixels.o : src/fragment/GLWritePixels.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_fragment_GLWritePixels.o -c src/fragment/GLWritePixels.cpp -Iinclude 
build/src_fragment_GLLightFunction.o : src/fragment/GLLightFunction.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_fragment_GLLightFunction.o -c src/fragment/GLLightFunction.cpp -Iinclude 
build/src_fragment_GLAbstractRasterizatedVarying.o : src/fragment/GLAbstractRasterizatedVarying.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_fragment_GLAbstractRasterizatedVarying.o -c src/fragment/GLAbstractRasterizatedVarying.cpp -Iinclude 
build/src_fragment_texture2D.o : src/fragment/texture2D.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_fragment_texture2D.o -c src/fragment/texture2D.cpp -Iinclude 
build/src_GL_GLTexture1Obj.o : src/GL/GLTexture1Obj.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLTexture1Obj.o -c src/GL/GLTexture1Obj.cpp -Iinclude 
build/src_GL_GLCamera.o : src/GL/GLCamera.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLCamera.o -c src/GL/GLCamera.cpp -Iinclude 
build/src_GL_GLBicubicWork.o : src/GL/GLBicubicWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLBicubicWork.o -c src/GL/GLBicubicWork.cpp -Iinclude 
build/src_GL_GLScene.o : src/GL/GLScene.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLScene.o -c src/GL/GLScene.cpp -Iinclude 
build/src_GL_GLFraction.o : src/GL/GLFraction.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLFraction.o -c src/GL/GLFraction.cpp -Iinclude 
build/src_GL_GLCurveObject.o : src/GL/GLCurveObject.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLCurveObject.o -c src/GL/GLCurveObject.cpp -Iinclude 
build/src_GL_GLFilterWork.o : src/GL/GLFilterWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLFilterWork.o -c src/GL/GLFilterWork.cpp -Iinclude 
build/src_GL_GLBezier.o : src/GL/GLBezier.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLBezier.o -c src/GL/GLBezier.cpp -Iinclude 
build/src_GL_GLProgram.o : src/GL/GLProgram.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLProgram.o -c src/GL/GLProgram.cpp -Iinclude 
build/src_GL_GLBitmapWorkFactory.o : src/GL/GLBitmapWorkFactory.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLBitmapWorkFactory.o -c src/GL/GLBitmapWorkFactory.cpp -Iinclude 
build/src_GL_GLLightScene.o : src/GL/GLLightScene.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLLightScene.o -c src/GL/GLLightScene.cpp -Iinclude 
build/src_GL_GLAutoProgram.o : src/GL/GLAutoProgram.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLAutoProgram.o -c src/GL/GLAutoProgram.cpp -Iinclude 
build/src_GL_GLTexture.o : src/GL/GLTexture.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLTexture.o -c src/GL/GLTexture.cpp -Iinclude 
build/src_GL_GLSquareObjectCreator.o : src/GL/GLSquareObjectCreator.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLSquareObjectCreator.o -c src/GL/GLSquareObjectCreator.cpp -Iinclude 
build/src_GL_GLMultiPassWork.o : src/GL/GLMultiPassWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLMultiPassWork.o -c src/GL/GLMultiPassWork.cpp -Iinclude 
build/src_GL_GLvboBuffer.o : src/GL/GLvboBuffer.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLvboBuffer.o -c src/GL/GLvboBuffer.cpp -Iinclude 
build/src_GL_GLBitmapWork.o : src/GL/GLBitmapWork.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLBitmapWork.o -c src/GL/GLBitmapWork.cpp -Iinclude 
build/src_GL_GLAutoFbo.o : src/GL/GLAutoFbo.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLAutoFbo.o -c src/GL/GLAutoFbo.cpp -Iinclude 
build/src_GL_GLWorkThread.o : src/GL/GLWorkThread.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_GL_GLWorkThread.o -c src/GL/GLWorkThread.cpp -Iinclude 
build/src_package_fragment.o : src/package/fragment.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_package_fragment.o -c src/package/fragment.cpp -Iinclude 
build/src_platform_GLLock.o : src/platform/GLLock.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_platform_GLLock.o -c src/platform/GLLock.cpp -Iinclude 
build/src_core_weightTable.o : src/core/weightTable.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_core_weightTable.o -c src/core/weightTable.cpp -Iinclude 
build/src_core_GLBmp.o : src/core/GLBmp.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_core_GLBmp.o -c src/core/GLBmp.cpp -Iinclude 
build/src_core_GLRasterization.o : src/core/GLRasterization.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_core_GLRasterization.o -c src/core/GLRasterization.cpp -Iinclude 
build/src_core_GLDepthBuffer.o : src/core/GLDepthBuffer.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_core_GLDepthBuffer.o -c src/core/GLDepthBuffer.cpp -Iinclude 
build/src_transform_GLBasicTransform.o : src/transform/GLBasicTransform.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_transform_GLBasicTransform.o -c src/transform/GLBasicTransform.cpp -Iinclude 
build/src_transform_ColorMover.o : src/transform/ColorMover.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_transform_ColorMover.o -c src/transform/ColorMover.cpp -Iinclude 
build/src_transform_SceneNewton.o : src/transform/SceneNewton.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_transform_SceneNewton.o -c src/transform/SceneNewton.cpp -Iinclude 
build/src_transform_GLFragPicture.o : src/transform/GLFragPicture.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_transform_GLFragPicture.o -c src/transform/GLFragPicture.cpp -Iinclude 
build/src_vertex_GLAbstractVarying.o : src/vertex/GLAbstractVarying.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_vertex_GLAbstractVarying.o -c src/vertex/GLAbstractVarying.cpp -Iinclude 
build/src_vertex_GL_position.o : src/vertex/GL_position.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_vertex_GL_position.o -c src/vertex/GL_position.cpp -Iinclude 
build/src_vertex_GL_Normal.o : src/vertex/GL_Normal.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_vertex_GL_Normal.o -c src/vertex/GL_Normal.cpp -Iinclude 
build/src_vertex_GLVectorVarying.o : src/vertex/GLVectorVarying.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_vertex_GLVectorVarying.o -c src/vertex/GLVectorVarying.cpp -Iinclude 
build/src_utils_GP_Clock.o : src/utils/GP_Clock.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_utils_GP_Clock.o -c src/utils/GP_Clock.cpp -Iinclude 
build/src_utils_GPRandom.o : src/utils/GPRandom.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_utils_GPRandom.o -c src/utils/GPRandom.cpp -Iinclude 
build/src_utils_GLThread.o : src/utils/GLThread.cpp   ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/src_utils_GLThread.o -c src/utils/GLThread.cpp -Iinclude 
build/src_utils_debug.o : src/utils/debug.c   ${ALL_INCLUESlibglsl.so}
	gcc -O3 -fPIC -o build/src_utils_debug.o -c src/utils/debug.c -Iinclude 

ALL_INCLUEStest.out= include/test/GLTest.h include/math/GLVector.h include/math/GLMatrix4.h include/math/GLSphere.h include/math/GLCurveSurface.h include/fragment/GL_FragTexcord.h include/fragment/GLAbstractRasterizatedVarying.h include/fragment/GL_FragPosition.h include/fragment/GLLightFunction.h include/fragment/GL_vPosition.h include/fragment/GLWritePixels.h include/fragment/GL_FragColor.h include/fragment/GLTexture2D.h include/GL/GLBicubicWork.h include/GL/GLBasicObjectCreator.h include/GL/GLMultiPassWork.h include/GL/GLTextureMultiObj.h include/GL/GLTransformer.h include/GL/GLAutoFbo.h include/GL/GLvboBuffer.h include/GL/GLAutoProgram.h include/GL/GLSquareObjectCreator.h include/GL/GLProgram.h include/GL/GLWork.h include/GL/GLTexture.h include/GL/GLBitmapWorkFactory.h include/GL/GLLightScene.h include/GL/GLBezier.h include/GL/debug.h include/GL/GLCamera.h include/GL/GLWorkThread.h include/GL/GLWorkHandler.h include/GL/GLBitmapWork.h include/GL/GLObject.h include/GL/GLCurveObject.h include/GL/GLTexture1Obj.h include/GL/GLFilterWork.h include/GL/head.h include/GL/GLScene.h include/package/vertex.h include/package/basic.h include/package/fragment.h include/package/package.h include/interface/IVertexFunction.h include/interface/IBitmap.h include/interface/IBasicVarying.h include/interface/GLColor.h include/interface/IFragmentFunction.h include/interface/IVarying.h include/interface/head.h include/interface/IRasterizatedVarying.h include/core/GLBmp.h include/core/GLDepthBuffer.h include/core/GLRasterization.h include/transform/GLFragPicture.h include/transform/GLBasicTransform.h include/vertex/GLVectorVarying.h include/vertex/GL_texcord.h include/vertex/GLAbstractVarying.h include/vertex/GL_Normal.h include/vertex/GL_position.h include/utils/RefCount.h include/utils/GLLock.h include/utils/debug.h include/utils/GP_Clock.h include/utils/GLThread.h include/utils/GPRandom.h

test.out:  build/test_main.o build/test_GLTest.o build/test_GLRotateTest.o build/test_GLSingleLightTest.o build/test_GLBmpTest.o build/test_GLRasterBasic.o build/test_GLProjectionTest.o build/test_GLFragTest.o libglsl.so
	g++  -O3 -fPIC -o test.out  build/test_main.o build/test_GLTest.o build/test_GLRotateTest.o build/test_GLSingleLightTest.o build/test_GLBmpTest.o build/test_GLRasterBasic.o build/test_GLProjectionTest.o build/test_GLFragTest.o  -lfreeimage ./libglsl.so -lGL -lGLEW ${SELF_VARIABLES}
build/test_main.o : test/main.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_main.o -c test/main.cpp -Iinclude 
build/test_GLTest.o : test/GLTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_GLTest.o -c test/GLTest.cpp -Iinclude 
build/test_GLRotateTest.o : test/GLRotateTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_GLRotateTest.o -c test/GLRotateTest.cpp -Iinclude 
build/test_GLSingleLightTest.o : test/GLSingleLightTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_GLSingleLightTest.o -c test/GLSingleLightTest.cpp -Iinclude 
build/test_GLBmpTest.o : test/GLBmpTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_GLBmpTest.o -c test/GLBmpTest.cpp -Iinclude 
build/test_GLRasterBasic.o : test/GLRasterBasic.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_GLRasterBasic.o -c test/GLRasterBasic.cpp -Iinclude 
build/test_GLProjectionTest.o : test/GLProjectionTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_GLProjectionTest.o -c test/GLProjectionTest.cpp -Iinclude 
build/test_GLFragTest.o : test/GLFragTest.cpp libglsl.so  ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_GLFragTest.o -c test/GLFragTest.cpp -Iinclude 

ALL_INCLUESgputest.out= include/test/GLTest.h include/math/GLVector.h include/math/GLMatrix4.h include/math/GLSphere.h include/math/GLCurveSurface.h include/fragment/GL_FragTexcord.h include/fragment/GLAbstractRasterizatedVarying.h include/fragment/GL_FragPosition.h include/fragment/GLLightFunction.h include/fragment/GL_vPosition.h include/fragment/GLWritePixels.h include/fragment/GL_FragColor.h include/fragment/GLTexture2D.h include/GL/GLBicubicWork.h include/GL/GLBasicObjectCreator.h include/GL/GLMultiPassWork.h include/GL/GLTextureMultiObj.h include/GL/GLTransformer.h include/GL/GLAutoFbo.h include/GL/GLvboBuffer.h include/GL/GLAutoProgram.h include/GL/GLSquareObjectCreator.h include/GL/GLProgram.h include/GL/GLWork.h include/GL/GLTexture.h include/GL/GLBitmapWorkFactory.h include/GL/GLLightScene.h include/GL/GLBezier.h include/GL/debug.h include/GL/GLCamera.h include/GL/GLWorkThread.h include/GL/GLWorkHandler.h include/GL/GLBitmapWork.h include/GL/GLObject.h include/GL/GLCurveObject.h include/GL/GLTexture1Obj.h include/GL/GLFilterWork.h include/GL/head.h include/GL/GLScene.h include/package/vertex.h include/package/basic.h include/package/fragment.h include/package/package.h include/interface/IVertexFunction.h include/interface/IBitmap.h include/interface/IBasicVarying.h include/interface/GLColor.h include/interface/IFragmentFunction.h include/interface/IVarying.h include/interface/head.h include/interface/IRasterizatedVarying.h include/core/GLBmp.h include/core/GLDepthBuffer.h include/core/GLRasterization.h include/transform/GLFragPicture.h include/transform/GLBasicTransform.h include/vertex/GLVectorVarying.h include/vertex/GL_texcord.h include/vertex/GLAbstractVarying.h include/vertex/GL_Normal.h include/vertex/GL_position.h include/utils/RefCount.h include/utils/GLLock.h include/utils/debug.h include/utils/GP_Clock.h include/utils/GLThread.h include/utils/GPRandom.h

gputest.out:  build/gltest_GLTest.o build/gltest_GLBitmapWorkTest.o build/gltest_GLCubicTest.o build/gltest_GLFilterTest.o build/gltest_GLFactoryTest.o build/gltest_GLFractionByGLTest.o build/gltest_opengltest_main.o build/gltest_GLWorkThreadTest.o libglsl.so
	g++  -O3 -fPIC -o gputest.out  build/gltest_GLTest.o build/gltest_GLBitmapWorkTest.o build/gltest_GLCubicTest.o build/gltest_GLFilterTest.o build/gltest_GLFactoryTest.o build/gltest_GLFractionByGLTest.o build/gltest_opengltest_main.o build/gltest_GLWorkThreadTest.o  -lfreeimage ./libglsl.so -lGLEW -lGL -lglut ${SELF_VARIABLES}
build/gltest_GLTest.o : gltest/GLTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -O3 -fPIC -o build/gltest_GLTest.o -c gltest/GLTest.cpp -Iinclude 
build/gltest_GLBitmapWorkTest.o : gltest/GLBitmapWorkTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -O3 -fPIC -o build/gltest_GLBitmapWorkTest.o -c gltest/GLBitmapWorkTest.cpp -Iinclude 
build/gltest_GLCubicTest.o : gltest/GLCubicTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -O3 -fPIC -o build/gltest_GLCubicTest.o -c gltest/GLCubicTest.cpp -Iinclude 
build/gltest_GLFilterTest.o : gltest/GLFilterTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -O3 -fPIC -o build/gltest_GLFilterTest.o -c gltest/GLFilterTest.cpp -Iinclude 
build/gltest_GLFactoryTest.o : gltest/GLFactoryTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -O3 -fPIC -o build/gltest_GLFactoryTest.o -c gltest/GLFactoryTest.cpp -Iinclude 
build/gltest_GLFractionByGLTest.o : gltest/GLFractionByGLTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -O3 -fPIC -o build/gltest_GLFractionByGLTest.o -c gltest/GLFractionByGLTest.cpp -Iinclude 
build/gltest_opengltest_main.o : gltest/opengltest_main.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -O3 -fPIC -o build/gltest_opengltest_main.o -c gltest/opengltest_main.cpp -Iinclude 
build/gltest_GLWorkThreadTest.o : gltest/GLWorkThreadTest.cpp libglsl.so  ${ALL_INCLUESgputest.out}
	g++ -O3 -fPIC -o build/gltest_GLWorkThreadTest.o -c gltest/GLWorkThreadTest.cpp -Iinclude 

ALL_INCLUESdisplay.out=

display.out:  build/_display_main.o libglsl.so
	g++  -O3 -fPIC -o display.out  build/_display_main.o  -lfreeimage ./libglsl.so -lGLEW -lGL -lglut -lm -lX11 ${SELF_VARIABLES}
build/_display_main.o : ./display_main.cpp libglsl.so  ${ALL_INCLUESdisplay.out}
	g++ -O3 -fPIC -o build/_display_main.o -c ./display_main.cpp -Iinclude 

clean:
	rm build/*.o
	rm libglsl.so
	rm test.out
	rm gputest.out
	rm display.out