all:libglsl.so test.out gputest.out display.out 

ALL_INCLUESlibglsl.so= include/core/GLBmp.h include/core/GLDepthBuffer.h include/core/GLRasterization.h include/fragment/GL_FragTexcord.h include/fragment/GLAbstractRasterizatedVarying.h include/fragment/GL_FragPosition.h include/fragment/GLLightFunction.h include/fragment/GL_vPosition.h include/fragment/GLWritePixels.h include/fragment/GL_FragColor.h include/fragment/GLTexture2D.h include/math/GLVector.h include/math/GLMatrix4.h include/math/GLSphere.h include/math/GLCurveSurface.h include/package/vertex.h include/package/basic.h include/package/fragment.h include/package/package.h include/transform/GLFragPicture.h include/transform/GLBasicTransform.h include/utils/RefCount.h include/utils/GLLock.h include/utils/debug.h include/utils/GP_Clock.h include/utils/GPRandom.h include/vertex/GLVectorVarying.h include/vertex/GL_texcord.h include/vertex/GLAbstractVarying.h include/vertex/GL_Normal.h include/vertex/GL_position.h include/GL/GLMultiPassWork.h include/GL/GLTextureMultiObj.h include/GL/GLTransformer.h include/GL/GLAutoFbo.h include/GL/GLvboBuffer.h include/GL/GLAutoProgram.h include/GL/GLProgram.h include/GL/GLWork.h include/GL/GLTexture.h include/GL/GLBitmapWorkFactory.h include/GL/GLLightScene.h include/GL/GLBezier.h include/GL/debug.h include/GL/GLCamera.h include/GL/GLBitmapWork.h include/GL/GLObject.h include/GL/GLCurveObject.h include/GL/GLTexture1Obj.h include/GL/GLFilterWork.h include/GL/head.h include/GL/GLScene.h

libglsl.so:  build/core_weightTable.o build/core_GLBmp.o build/core_GLRasterization.o build/core_GLDepthBuffer.o build/fragment_GLWritePixels.o build/fragment_GLLightFunction.o build/fragment_GLAbstractRasterizatedVarying.o build/fragment_texture2D.o build/math_GLMatrix.o build/math_GLVector.o build/math_GLSphere.o build/package_fragment.o build/transform_GLBasicTransform.o build/transform_ColorMover.o build/transform_SceneNewton.o build/transform_GLFragPicture.o build/utils_GP_Clock.o build/utils_GPRandom.o build/vertex_GLAbstractVarying.o build/vertex_GL_position.o build/vertex_GL_Normal.o build/vertex_GLVectorVarying.o build/GL_GLTexture1Obj.o build/GL_GLCamera.o build/GL_GLScene.o build/GL_GLFraction.o build/GL_GLCurveObject.o build/GL_GLFilterWork.o build/GL_GLBezier.o build/GL_GLProgram.o build/GL_GLBitmapWorkFactory.o build/GL_GLLightScene.o build/GL_GLAutoProgram.o build/GL_GLTexture.o build/GL_GLMultiPassWork.o build/GL_GLvboBuffer.o build/GL_GLBitmapWork.o build/GL_GLAutoFbo.o build/platform_GLLock.o build/utils_debug.o 
	g++  -O3 -fPIC --share  -o libglsl.so  build/core_weightTable.o build/core_GLBmp.o build/core_GLRasterization.o build/core_GLDepthBuffer.o build/fragment_GLWritePixels.o build/fragment_GLLightFunction.o build/fragment_GLAbstractRasterizatedVarying.o build/fragment_texture2D.o build/math_GLMatrix.o build/math_GLVector.o build/math_GLSphere.o build/package_fragment.o build/transform_GLBasicTransform.o build/transform_ColorMover.o build/transform_SceneNewton.o build/transform_GLFragPicture.o build/utils_GP_Clock.o build/utils_GPRandom.o build/vertex_GLAbstractVarying.o build/vertex_GL_position.o build/vertex_GL_Normal.o build/vertex_GLVectorVarying.o build/GL_GLTexture1Obj.o build/GL_GLCamera.o build/GL_GLScene.o build/GL_GLFraction.o build/GL_GLCurveObject.o build/GL_GLFilterWork.o build/GL_GLBezier.o build/GL_GLProgram.o build/GL_GLBitmapWorkFactory.o build/GL_GLLightScene.o build/GL_GLAutoProgram.o build/GL_GLTexture.o build/GL_GLMultiPassWork.o build/GL_GLvboBuffer.o build/GL_GLBitmapWork.o build/GL_GLAutoFbo.o build/platform_GLLock.o build/utils_debug.o  -lfreeimage  ${SELF_VARIABLES}
build/core_weightTable.o : src/core/weightTable.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/core_weightTable.o -c src/core/weightTable.cpp -Iinclude 
build/core_GLBmp.o : src/core/GLBmp.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/core_GLBmp.o -c src/core/GLBmp.cpp -Iinclude 
build/core_GLRasterization.o : src/core/GLRasterization.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/core_GLRasterization.o -c src/core/GLRasterization.cpp -Iinclude 
build/core_GLDepthBuffer.o : src/core/GLDepthBuffer.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/core_GLDepthBuffer.o -c src/core/GLDepthBuffer.cpp -Iinclude 
build/fragment_GLWritePixels.o : src/fragment/GLWritePixels.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/fragment_GLWritePixels.o -c src/fragment/GLWritePixels.cpp -Iinclude 
build/fragment_GLLightFunction.o : src/fragment/GLLightFunction.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/fragment_GLLightFunction.o -c src/fragment/GLLightFunction.cpp -Iinclude 
build/fragment_GLAbstractRasterizatedVarying.o : src/fragment/GLAbstractRasterizatedVarying.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/fragment_GLAbstractRasterizatedVarying.o -c src/fragment/GLAbstractRasterizatedVarying.cpp -Iinclude 
build/fragment_texture2D.o : src/fragment/texture2D.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/fragment_texture2D.o -c src/fragment/texture2D.cpp -Iinclude 
build/math_GLMatrix.o : src/math/GLMatrix.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/math_GLMatrix.o -c src/math/GLMatrix.cpp -Iinclude 
build/math_GLVector.o : src/math/GLVector.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/math_GLVector.o -c src/math/GLVector.cpp -Iinclude 
build/math_GLSphere.o : src/math/GLSphere.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/math_GLSphere.o -c src/math/GLSphere.cpp -Iinclude 
build/package_fragment.o : src/package/fragment.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/package_fragment.o -c src/package/fragment.cpp -Iinclude 
build/transform_GLBasicTransform.o : src/transform/GLBasicTransform.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/transform_GLBasicTransform.o -c src/transform/GLBasicTransform.cpp -Iinclude 
build/transform_ColorMover.o : src/transform/ColorMover.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/transform_ColorMover.o -c src/transform/ColorMover.cpp -Iinclude 
build/transform_SceneNewton.o : src/transform/SceneNewton.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/transform_SceneNewton.o -c src/transform/SceneNewton.cpp -Iinclude 
build/transform_GLFragPicture.o : src/transform/GLFragPicture.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/transform_GLFragPicture.o -c src/transform/GLFragPicture.cpp -Iinclude 
build/utils_GP_Clock.o : src/utils/GP_Clock.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/utils_GP_Clock.o -c src/utils/GP_Clock.cpp -Iinclude 
build/utils_GPRandom.o : src/utils/GPRandom.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/utils_GPRandom.o -c src/utils/GPRandom.cpp -Iinclude 
build/vertex_GLAbstractVarying.o : src/vertex/GLAbstractVarying.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/vertex_GLAbstractVarying.o -c src/vertex/GLAbstractVarying.cpp -Iinclude 
build/vertex_GL_position.o : src/vertex/GL_position.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/vertex_GL_position.o -c src/vertex/GL_position.cpp -Iinclude 
build/vertex_GL_Normal.o : src/vertex/GL_Normal.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/vertex_GL_Normal.o -c src/vertex/GL_Normal.cpp -Iinclude 
build/vertex_GLVectorVarying.o : src/vertex/GLVectorVarying.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/vertex_GLVectorVarying.o -c src/vertex/GLVectorVarying.cpp -Iinclude 
build/GL_GLTexture1Obj.o : src/GL/GLTexture1Obj.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLTexture1Obj.o -c src/GL/GLTexture1Obj.cpp -Iinclude 
build/GL_GLCamera.o : src/GL/GLCamera.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLCamera.o -c src/GL/GLCamera.cpp -Iinclude 
build/GL_GLScene.o : src/GL/GLScene.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLScene.o -c src/GL/GLScene.cpp -Iinclude 
build/GL_GLFraction.o : src/GL/GLFraction.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLFraction.o -c src/GL/GLFraction.cpp -Iinclude 
build/GL_GLCurveObject.o : src/GL/GLCurveObject.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLCurveObject.o -c src/GL/GLCurveObject.cpp -Iinclude 
build/GL_GLFilterWork.o : src/GL/GLFilterWork.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLFilterWork.o -c src/GL/GLFilterWork.cpp -Iinclude 
build/GL_GLBezier.o : src/GL/GLBezier.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLBezier.o -c src/GL/GLBezier.cpp -Iinclude 
build/GL_GLProgram.o : src/GL/GLProgram.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLProgram.o -c src/GL/GLProgram.cpp -Iinclude 
build/GL_GLBitmapWorkFactory.o : src/GL/GLBitmapWorkFactory.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLBitmapWorkFactory.o -c src/GL/GLBitmapWorkFactory.cpp -Iinclude 
build/GL_GLLightScene.o : src/GL/GLLightScene.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLLightScene.o -c src/GL/GLLightScene.cpp -Iinclude 
build/GL_GLAutoProgram.o : src/GL/GLAutoProgram.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLAutoProgram.o -c src/GL/GLAutoProgram.cpp -Iinclude 
build/GL_GLTexture.o : src/GL/GLTexture.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLTexture.o -c src/GL/GLTexture.cpp -Iinclude 
build/GL_GLMultiPassWork.o : src/GL/GLMultiPassWork.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLMultiPassWork.o -c src/GL/GLMultiPassWork.cpp -Iinclude 
build/GL_GLvboBuffer.o : src/GL/GLvboBuffer.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLvboBuffer.o -c src/GL/GLvboBuffer.cpp -Iinclude 
build/GL_GLBitmapWork.o : src/GL/GLBitmapWork.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLBitmapWork.o -c src/GL/GLBitmapWork.cpp -Iinclude 
build/GL_GLAutoFbo.o : src/GL/GLAutoFbo.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/GL_GLAutoFbo.o -c src/GL/GLAutoFbo.cpp -Iinclude 
build/platform_GLLock.o : src/platform/GLLock.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -fPIC -o build/platform_GLLock.o -c src/platform/GLLock.cpp -Iinclude 
build/utils_debug.o : src/utils/debug.c ${ALL_INCLUESlibglsl.so}
	gcc -O3 -fPIC -o build/utils_debug.o -c src/utils/debug.c -Iinclude 

ALL_INCLUEStest.out= include/test/GLTest.h

test.out:  build/test_GLTest.o build/test_GLRotateTest.o build/test_GLSingleLightTest.o build/test_GLBmpTest.o build/test_GLRasterBasic.o build/test_GLProjectionTest.o build/test_GLFragTest.o build/main.o libglsl.so
	g++  -O3 -fPIC -o test.out  build/test_GLTest.o build/test_GLRotateTest.o build/test_GLSingleLightTest.o build/test_GLBmpTest.o build/test_GLRasterBasic.o build/test_GLProjectionTest.o build/test_GLFragTest.o build/main.o  -lfreeimage ./libglsl.so -lGL -lGLEW ${SELF_VARIABLES}
build/test_GLTest.o : src/test/GLTest.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_GLTest.o -c src/test/GLTest.cpp -Iinclude 
build/test_GLRotateTest.o : src/test/GLRotateTest.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_GLRotateTest.o -c src/test/GLRotateTest.cpp -Iinclude 
build/test_GLSingleLightTest.o : src/test/GLSingleLightTest.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_GLSingleLightTest.o -c src/test/GLSingleLightTest.cpp -Iinclude 
build/test_GLBmpTest.o : src/test/GLBmpTest.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_GLBmpTest.o -c src/test/GLBmpTest.cpp -Iinclude 
build/test_GLRasterBasic.o : src/test/GLRasterBasic.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_GLRasterBasic.o -c src/test/GLRasterBasic.cpp -Iinclude 
build/test_GLProjectionTest.o : src/test/GLProjectionTest.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_GLProjectionTest.o -c src/test/GLProjectionTest.cpp -Iinclude 
build/test_GLFragTest.o : src/test/GLFragTest.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/test_GLFragTest.o -c src/test/GLFragTest.cpp -Iinclude 
build/main.o : ./main.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -fPIC -o build/main.o -c ./main.cpp -Iinclude 

ALL_INCLUESgputest.out=

gputest.out:  build/gltest_GLTest.o build/gltest_GLBitmapWorkTest.o build/gltest_GLFilterTest.o build/gltest_GLFactoryTest.o build/gltest_GLFractionByGLTest.o build/opengltest_main.o libglsl.so
	g++  -O3 -fPIC -o gputest.out  build/gltest_GLTest.o build/gltest_GLBitmapWorkTest.o build/gltest_GLFilterTest.o build/gltest_GLFactoryTest.o build/gltest_GLFractionByGLTest.o build/opengltest_main.o  -lfreeimage ./libglsl.so -lGLEW -lGL -lglut ${SELF_VARIABLES}
build/gltest_GLTest.o : src/gltest/GLTest.cpp ${ALL_INCLUESgputest.out}
	g++ -O3 -fPIC -o build/gltest_GLTest.o -c src/gltest/GLTest.cpp -Iinclude 
build/gltest_GLBitmapWorkTest.o : src/gltest/GLBitmapWorkTest.cpp ${ALL_INCLUESgputest.out}
	g++ -O3 -fPIC -o build/gltest_GLBitmapWorkTest.o -c src/gltest/GLBitmapWorkTest.cpp -Iinclude 
build/gltest_GLFilterTest.o : src/gltest/GLFilterTest.cpp ${ALL_INCLUESgputest.out}
	g++ -O3 -fPIC -o build/gltest_GLFilterTest.o -c src/gltest/GLFilterTest.cpp -Iinclude 
build/gltest_GLFactoryTest.o : src/gltest/GLFactoryTest.cpp ${ALL_INCLUESgputest.out}
	g++ -O3 -fPIC -o build/gltest_GLFactoryTest.o -c src/gltest/GLFactoryTest.cpp -Iinclude 
build/gltest_GLFractionByGLTest.o : src/gltest/GLFractionByGLTest.cpp ${ALL_INCLUESgputest.out}
	g++ -O3 -fPIC -o build/gltest_GLFractionByGLTest.o -c src/gltest/GLFractionByGLTest.cpp -Iinclude 
build/opengltest_main.o : ./opengltest_main.cpp ${ALL_INCLUESgputest.out}
	g++ -O3 -fPIC -o build/opengltest_main.o -c ./opengltest_main.cpp -Iinclude 

ALL_INCLUESdisplay.out=

display.out:  build/display_main.o libglsl.so
	g++  -O3 -fPIC -o display.out  build/display_main.o  -lfreeimage ./libglsl.so -lGLEW -lGL -lglut -lm -lX11 ${SELF_VARIABLES}
build/display_main.o : ./display_main.cpp ${ALL_INCLUESdisplay.out}
	g++ -O3 -fPIC -o build/display_main.o -c ./display_main.cpp -Iinclude 

clean:
	rm build/*.o
	rm libglsl.so
	rm test.out
	rm gputest.out
	rm display.out