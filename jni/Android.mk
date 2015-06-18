# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
define all-cpp-files
$(shell find $(LOCAL_PATH)/../src -name "*.cpp")
endef

LOCAL_MODULE    := libsimple3D
LOCAL_CFLAGS    := -Werror
LOCAL_CFLAGS    += -DGL_BUILD_FOR_ANDROID
LOCAL_SRC_FILES := \
	$(LOCAL_PATH)/../src//core/GLBmp.cpp\
	$(LOCAL_PATH)/../src//core/GLBmpFactory.cpp\
	$(LOCAL_PATH)/../src//core/GLDepthBuffer.cpp\
	$(LOCAL_PATH)/../src//core/GLRasterization.cpp\
	$(LOCAL_PATH)/../src//core/weightTable.cpp\
	$(LOCAL_PATH)/../src//fragment/GLAbstractRasterizatedVarying.cpp\
	$(LOCAL_PATH)/../src//fragment/GLLightFunction.cpp\
	$(LOCAL_PATH)/../src//fragment/GLWritePixels.cpp\
	$(LOCAL_PATH)/../src//fragment/texture2D.cpp\
	$(LOCAL_PATH)/../src//GL/GLAutoFbo.cpp\
	$(LOCAL_PATH)/../src//GL/GLAutoProgram.cpp\
	$(LOCAL_PATH)/../src//GL/GLBezier.cpp\
	$(LOCAL_PATH)/../src//GL/GLBiCubicCurveObj.cpp\
	$(LOCAL_PATH)/../src//GL/GLBicubicWork.cpp\
	$(LOCAL_PATH)/../src//GL/GLBitmapWork.cpp\
	$(LOCAL_PATH)/../src//GL/GLBitmapWorkFactory.cpp\
	$(LOCAL_PATH)/../src//GL/GLCamera.cpp\
	$(LOCAL_PATH)/../src//GL/GLCurveObject.cpp\
	$(LOCAL_PATH)/../src//GL/GLCurveObjectFactory.cpp\
	$(LOCAL_PATH)/../src//GL/GLFilterWork.cpp\
	$(LOCAL_PATH)/../src//GL/GLFraction.cpp\
	$(LOCAL_PATH)/../src//GL/GLLightCurveObject.cpp\
	$(LOCAL_PATH)/../src//GL/GLLightScene.cpp\
	$(LOCAL_PATH)/../src//GL/GLMixWork.cpp\
	$(LOCAL_PATH)/../src//GL/GLMultiPassWork.cpp\
	$(LOCAL_PATH)/../src//GL/GLProgram.cpp\
	$(LOCAL_PATH)/../src//GL/GLScene.cpp\
	$(LOCAL_PATH)/../src//GL/GLSquareObjectCreator.cpp\
	$(LOCAL_PATH)/../src//GL/GLTexture.cpp\
	$(LOCAL_PATH)/../src//GL/GLTexture1Obj.cpp\
	$(LOCAL_PATH)/../src//GL/GLTextureWork.cpp\
	$(LOCAL_PATH)/../src//GL/GLvboBuffer.cpp\
	$(LOCAL_PATH)/../src//GL/GLWorkThread.cpp\
	$(LOCAL_PATH)/../src//math/AbstractPoint.cpp\
	$(LOCAL_PATH)/../src//math/BasicFunctionDeter.cpp\
	$(LOCAL_PATH)/../src//math/FormulaTree.cpp\
	$(LOCAL_PATH)/../src//math/GLMatrix.cpp\
	$(LOCAL_PATH)/../src//math/GLSphere.cpp\
	$(LOCAL_PATH)/../src//math/GLVector.cpp\
	$(LOCAL_PATH)/../src//platform/GLContext.cpp\
	$(LOCAL_PATH)/../src//platform/GLLock.cpp\
	$(LOCAL_PATH)/../src//transform/ColorMover.cpp\
	$(LOCAL_PATH)/../src//transform/GLBasicTransform.cpp\
	$(LOCAL_PATH)/../src//transform/GLFragPicture.cpp\
	$(LOCAL_PATH)/../src//transform/SceneNewton.cpp\
	$(LOCAL_PATH)/../src//utils/GLThread.cpp\
	$(LOCAL_PATH)/../src//utils/GP_Clock.cpp\
	$(LOCAL_PATH)/../src//utils/GPRandom.cpp\
	$(LOCAL_PATH)/../src//vertex/GL_Normal.cpp\
	$(LOCAL_PATH)/../src//vertex/GL_position.cpp\
	$(LOCAL_PATH)/../src//vertex/GLAbstractVarying.cpp\
	$(LOCAL_PATH)/../src//vertex/GLVectorVarying.cpp

LOCAL_SRC_FILES += ../glsl/AllShader.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include/\

LOCAL_LDLIBS    := -lz -lm -llog -lGLESv2 -lEGL
LOCAL_CPP_FEATURES := rtti exceptions

include $(BUILD_SHARED_LIBRARY)

