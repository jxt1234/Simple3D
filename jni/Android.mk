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
LOCAL_SRC_FILES := $(call all-cpp-files)

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include/\
    $(LOCAL_PATH)/../third_party/FreeImage/Source

LOCAL_STATIC_LIBRARIES+= FreeImage
LOCAL_LDLIBS    := -lz -lm -llog -lGLESv2
LOCAL_CPP_FEATURES := rtti exceptions

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
define jpeg-files
$(shell find $(LOCAL_PATH)/Source/LibJPEG -name "j*.c")
endef
LOCAL_PATH:=$(LOCAL_PATH)/../third_party/FreeImage
include $(LOCAL_PATH)/Makefile.srcs
LOCAL_MODULE    := FreeImage
LOCAL_C_INCLUDES +=\
                   $(LOCAL_PATH)/Source/ \
                   $(LOCAL_PATH)/Source/Metadata \
                   $(LOCAL_PATH)/Source/FreeImageToolkit \
                   $(LOCAL_PATH)/Source/LibJPEG \
                   $(LOCAL_PATH)/Source/LibPNG \
                   $(LOCAL_PATH)/Source/LibTIFF4 \
                   $(LOCAL_PATH)/Source/ZLib \
                   $(LOCAL_PATH)/Source/LibOpenJPEG \
                   $(LOCAL_PATH)/Source/OpenEXR \
                   $(LOCAL_PATH)/Source/OpenEXR/Half \
                   $(LOCAL_PATH)/Source/OpenEXR/Iex \
                   $(LOCAL_PATH)/Source/OpenEXR/IlmImf \
                   $(LOCAL_PATH)/Source/OpenEXR/IlmThread \
                   $(LOCAL_PATH)/Source/OpenEXR/Imath \
                   $(LOCAL_PATH)/Source/LibRawLite \
                   $(LOCAL_PATH)/Source/LibRawLite/dcraw \
                   $(LOCAL_PATH)/Source/LibRawLite/internal \
                   $(LOCAL_PATH)/Source/LibRawLite/libraw \
                   $(LOCAL_PATH)/Source/LibRawLite/src

LOCAL_CPP_FEATURES := rtti exceptions
LOCAL_SRC_FILES := \
                   $(SRCS)\

include $(BUILD_STATIC_LIBRARY)
