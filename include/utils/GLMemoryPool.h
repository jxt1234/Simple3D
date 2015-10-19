/*Created by j00225966*/
/*This memory pool can't free, and is not thread safe*/
#ifndef GLMEMORYPOOL_H
#define GLMEMORYPOOL_H
#include <stdlib.h>
#ifdef __cplusplus
extern "C"{
#endif

typedef struct GLMemoryPool GLMemoryPool;

GLMemoryPool* GLMemoryPoolCreate(size_t blocksize);
void GLMemoryPoolDestroy(GLMemoryPool* pool);
void* GLMemoryPoolAlloc(GLMemoryPool* pool, size_t size);
void* GLMemoryPoolAllocInBlock(GLMemoryPool* pool, size_t size);
#ifdef __cplusplus
}
#endif
#endif
