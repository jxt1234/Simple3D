/******************************************************************
   Copyright 2013, Jiang Xiao-tang

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
******************************************************************/
#ifndef SIMPLE3D_DEBUG_H
#define SIMPLE3D_DEBUG_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define DEBUG_ON

#ifdef DEBUG_ON
#ifdef GL_BUILD_FOR_ANDROID
#include <android/log.h>
#define GPPRINT(format, ...) __android_log_print(ANDROID_LOG_INFO, "simple3D", format,##__VA_ARGS__)
#else
#define GPPRINT(format, ...) printf(format,##__VA_ARGS__)
#endif

#define FUNC_PRINT(x) GPPRINT(#x"=%d in %s, %d \n",x,  __func__, __LINE__);
#define FUNC_PRINT_ALL(x, type) GPPRINT(#x"="#type"%"#type" in %s, %d \n",x,  __func__, __LINE__);

#define CHECK_POINTER(x) {if(NULL==x){FUNC_PRINT_ALL(x,p);break;}}

#ifndef GL_BUILD_FOR_ANDROID
#define GLASSERT(x) assert(x)
#else
#define GLASSERT(x) \
    {bool result = (x);\
        if (!(result))\
        FUNC_PRINT((result));}
#endif
#else

#define FUNC_PRINT(x)
#define FUNC_PRINT_ALL(x, type)
#define CHECK_POINTER(x)

#endif

#define GPASSERT(x) GLASSERT(x)

#ifdef __cplusplus
extern "C"{
#endif
void dump_stack();
#ifdef __cplusplus
}
#endif

#endif
