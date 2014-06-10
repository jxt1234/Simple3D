all:libglsl.so test.out display.out 

ALL_INCLUESlibglsl.so= include/core/GLFloatBmp.h include/core/GLBmp.h include/core/GLDepthBuffer.h include/core/GLRasterization.h include/fragment/GL_FragTexcord.h include/fragment/GLAbstractRasterizatedVarying.h include/fragment/GL_FragPosition.h include/fragment/GLLightFunction.h include/fragment/GL_vPosition.h include/fragment/texture2D.h include/fragment/GLWritePixels.h include/fragment/GL_FragColor.h include/math/GLVector.h include/math/GLMatrix4.h include/math/GLSphere.h include/math/GLCurveSurface.h include/package/vertex.h include/package/basic.h include/package/fragment.h include/package/package.h include/transform/GLFragPicture.h include/transform/GLBasicTransform.h include/utils/debug.h include/vertex/GLVectorVarying.h include/vertex/GL_texcord.h include/vertex/GLAbstractVarying.h include/vertex/GL_Normal.h include/vertex/GL_position.h

libglsl.so:  build/core_weightTable.o build/core_GLBmp.o build/core_GLRasterization.o build/core_GLDepthBuffer.o build/fragment_GLWritePixels.o build/fragment_GLLightFunction.o build/fragment_GLAbstractRasterizatedVarying.o build/fragment_texture2D.o build/math_GLMatrix.o build/math_GLVector.o build/math_GLSphere.o build/package_fragment.o build/transform_GLBasicTransform.o build/transform_ColorMover.o build/transform_SceneNewton.o build/transform_GLFragPicture.o build/vertex_GLAbstractVarying.o build/vertex_GL_position.o build/vertex_GL_Normal.o build/vertex_GLVectorVarying.o build/utils_debug.o 
	g++  -O3 --share  -o libglsl.so  build/core_weightTable.o build/core_GLBmp.o build/core_GLRasterization.o build/core_GLDepthBuffer.o build/fragment_GLWritePixels.o build/fragment_GLLightFunction.o build/fragment_GLAbstractRasterizatedVarying.o build/fragment_texture2D.o build/math_GLMatrix.o build/math_GLVector.o build/math_GLSphere.o build/package_fragment.o build/transform_GLBasicTransform.o build/transform_ColorMover.o build/transform_SceneNewton.o build/transform_GLFragPicture.o build/vertex_GLAbstractVarying.o build/vertex_GL_position.o build/vertex_GL_Normal.o build/vertex_GLVectorVarying.o build/utils_debug.o  -lfreeimage  ${SELF_VARIABLES}
build/core_weightTable.o : src/core/weightTable.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/core_weightTable.o -c src/core/weightTable.cpp -Iinclude 
build/core_GLBmp.o : src/core/GLBmp.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/core_GLBmp.o -c src/core/GLBmp.cpp -Iinclude 
build/core_GLRasterization.o : src/core/GLRasterization.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/core_GLRasterization.o -c src/core/GLRasterization.cpp -Iinclude 
build/core_GLDepthBuffer.o : src/core/GLDepthBuffer.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/core_GLDepthBuffer.o -c src/core/GLDepthBuffer.cpp -Iinclude 
build/fragment_GLWritePixels.o : src/fragment/GLWritePixels.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/fragment_GLWritePixels.o -c src/fragment/GLWritePixels.cpp -Iinclude 
build/fragment_GLLightFunction.o : src/fragment/GLLightFunction.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/fragment_GLLightFunction.o -c src/fragment/GLLightFunction.cpp -Iinclude 
build/fragment_GLAbstractRasterizatedVarying.o : src/fragment/GLAbstractRasterizatedVarying.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/fragment_GLAbstractRasterizatedVarying.o -c src/fragment/GLAbstractRasterizatedVarying.cpp -Iinclude 
build/fragment_texture2D.o : src/fragment/texture2D.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/fragment_texture2D.o -c src/fragment/texture2D.cpp -Iinclude 
build/math_GLMatrix.o : src/math/GLMatrix.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/math_GLMatrix.o -c src/math/GLMatrix.cpp -Iinclude 
build/math_GLVector.o : src/math/GLVector.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/math_GLVector.o -c src/math/GLVector.cpp -Iinclude 
build/math_GLSphere.o : src/math/GLSphere.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/math_GLSphere.o -c src/math/GLSphere.cpp -Iinclude 
build/package_fragment.o : src/package/fragment.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/package_fragment.o -c src/package/fragment.cpp -Iinclude 
build/transform_GLBasicTransform.o : src/transform/GLBasicTransform.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/transform_GLBasicTransform.o -c src/transform/GLBasicTransform.cpp -Iinclude 
build/transform_ColorMover.o : src/transform/ColorMover.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/transform_ColorMover.o -c src/transform/ColorMover.cpp -Iinclude 
build/transform_SceneNewton.o : src/transform/SceneNewton.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/transform_SceneNewton.o -c src/transform/SceneNewton.cpp -Iinclude 
build/transform_GLFragPicture.o : src/transform/GLFragPicture.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/transform_GLFragPicture.o -c src/transform/GLFragPicture.cpp -Iinclude 
build/vertex_GLAbstractVarying.o : src/vertex/GLAbstractVarying.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/vertex_GLAbstractVarying.o -c src/vertex/GLAbstractVarying.cpp -Iinclude 
build/vertex_GL_position.o : src/vertex/GL_position.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/vertex_GL_position.o -c src/vertex/GL_position.cpp -Iinclude 
build/vertex_GL_Normal.o : src/vertex/GL_Normal.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/vertex_GL_Normal.o -c src/vertex/GL_Normal.cpp -Iinclude 
build/vertex_GLVectorVarying.o : src/vertex/GLVectorVarying.cpp ${ALL_INCLUESlibglsl.so}
	g++ -O3 -o build/vertex_GLVectorVarying.o -c src/vertex/GLVectorVarying.cpp -Iinclude 
build/utils_debug.o : src/utils/debug.c ${ALL_INCLUESlibglsl.so}
	gcc -O3 -o build/utils_debug.o -c src/utils/debug.c -Iinclude 

ALL_INCLUEStest.out= include/test/GLTest.h

test.out:  build/test_GLTest.o build/test_GLRotateTest.o build/test_GLSingleLightTest.o build/test_GLBmpTest.o build/test_GLRasterBasic.o build/test_GLProjectionTest.o build/test_GLFragTest.o build/main.o libglsl.so
	g++  -O3 -o test.out  build/test_GLTest.o build/test_GLRotateTest.o build/test_GLSingleLightTest.o build/test_GLBmpTest.o build/test_GLRasterBasic.o build/test_GLProjectionTest.o build/test_GLFragTest.o build/main.o  -lfreeimage ./libglsl.so  ${SELF_VARIABLES}
build/test_GLTest.o : src/test/GLTest.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -o build/test_GLTest.o -c src/test/GLTest.cpp -Iinclude 
build/test_GLRotateTest.o : src/test/GLRotateTest.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -o build/test_GLRotateTest.o -c src/test/GLRotateTest.cpp -Iinclude 
build/test_GLSingleLightTest.o : src/test/GLSingleLightTest.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -o build/test_GLSingleLightTest.o -c src/test/GLSingleLightTest.cpp -Iinclude 
build/test_GLBmpTest.o : src/test/GLBmpTest.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -o build/test_GLBmpTest.o -c src/test/GLBmpTest.cpp -Iinclude 
build/test_GLRasterBasic.o : src/test/GLRasterBasic.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -o build/test_GLRasterBasic.o -c src/test/GLRasterBasic.cpp -Iinclude 
build/test_GLProjectionTest.o : src/test/GLProjectionTest.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -o build/test_GLProjectionTest.o -c src/test/GLProjectionTest.cpp -Iinclude 
build/test_GLFragTest.o : src/test/GLFragTest.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -o build/test_GLFragTest.o -c src/test/GLFragTest.cpp -Iinclude 
build/main.o : ./main.cpp ${ALL_INCLUEStest.out}
	g++ -O3 -o build/main.o -c ./main.cpp -Iinclude 

ALL_INCLUESdisplay.out= include/display/texture.h include/display/vboBuffer.h include/display/scene.h include/display/object.h include/display/debug.h include/display/program.h include/display/head.h

display.out:  build/display_program.o build/display_vboBuffer_gles2.o build/display_texture_gles2.o build/display_program_gles2.o build/display_texture.o build/display.o libglsl.so
	g++  -O3 -o display.out  build/display_program.o build/display_vboBuffer_gles2.o build/display_texture_gles2.o build/display_program_gles2.o build/display_texture.o build/display.o  -lfreeimage ./libglsl.so -lGLEW -lGL -lglut -lm -lX11 ${SELF_VARIABLES}
build/display_program.o : src/display/program.cpp ${ALL_INCLUESdisplay.out}
	g++ -O3 -o build/display_program.o -c src/display/program.cpp -Iinclude 
build/display_vboBuffer_gles2.o : src/display/vboBuffer_gles2.cpp ${ALL_INCLUESdisplay.out}
	g++ -O3 -o build/display_vboBuffer_gles2.o -c src/display/vboBuffer_gles2.cpp -Iinclude 
build/display_texture_gles2.o : src/display/texture_gles2.cpp ${ALL_INCLUESdisplay.out}
	g++ -O3 -o build/display_texture_gles2.o -c src/display/texture_gles2.cpp -Iinclude 
build/display_program_gles2.o : src/display/program_gles2.cpp ${ALL_INCLUESdisplay.out}
	g++ -O3 -o build/display_program_gles2.o -c src/display/program_gles2.cpp -Iinclude 
build/display_texture.o : src/display/texture.cpp ${ALL_INCLUESdisplay.out}
	g++ -O3 -o build/display_texture.o -c src/display/texture.cpp -Iinclude 
build/display.o : ./display.cpp ${ALL_INCLUESdisplay.out}
	g++ -O3 -o build/display.o -c ./display.cpp -Iinclude 

clean:
	rm build/*.o
	rm libglsl.so
	rm test.out
	rm display.out