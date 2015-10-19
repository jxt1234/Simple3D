/*Created by j00225966*/
#include "utils/debug.h"
#include "utils/GLMemoryPool.h"
#include <stdlib.h>
#define ALIGN_UP(x, i) (((x) + i -1)/i*i)
typedef struct Block
{
    void* basic;
    struct Block* next;
    size_t offset;
    size_t size;
} Block;

struct GLMemoryPool
{
    Block* head;
    Block* current;
    size_t blocksize;
};

static Block* _BlockCreate(size_t blocksize)
{
    Block* b = (Block*)malloc(sizeof(Block));
    GLASSERT(NULL!=b);
    b->basic = malloc(blocksize);
    GLASSERT(NULL!=b->basic);
    b->size = blocksize;
    b->next = NULL;
    b->offset = 0;
    return b;
}

static void _BlockDestroy(Block* b)
{
    GLASSERT(NULL!=b);
    GLASSERT(NULL!=b->basic);
    free(b->basic);
    free(b);
}


GLMemoryPool* GLMemoryPoolCreate(size_t blocksize)
{
    GLMemoryPool* pool = (GLMemoryPool*)malloc(sizeof(GLMemoryPool));
    GLASSERT(NULL!=pool);
    pool->blocksize = blocksize;
    pool->head = _BlockCreate(blocksize);
    GLASSERT(NULL!=pool->head);
    pool->current = pool->head;
    return pool;
}
void GLMemoryPoolDestroy(GLMemoryPool* pool)
{
    Block* current;
    Block* before = NULL;
    GLASSERT(NULL != pool);
    current = pool->head;
    while (NULL != current)
    {
        before = current;
        current = before->next;
        _BlockDestroy(before);
    }
    free(pool);
}
void* GLMemoryPoolAlloc(GLMemoryPool* pool, size_t size)
{
    Block* current;
    void* result;
    GLASSERT(NULL!=pool);
    GLASSERT(0 < size);
    GLASSERT(NULL!=pool->current);
    size = ALIGN_UP(size, 8);
    if(size > pool->blocksize)
    {
        /*Alloc a Spectial block with this large size*/
        Block* prev;
        current = _BlockCreate(size);
        /*Find the prev block of pool->current*/
        for (prev=pool->head; NULL!=prev && prev->next!=pool->current; prev = prev->next)
        {
            GLASSERT(NULL!=prev);
        }
        if (NULL == prev)
        {
            current->next = pool->head;
            pool->head = current;
        }
        else
        {
            prev->next = current;
            current->next = pool->current;
        }
        return current->basic;
    }
    current = pool->current;
    if (current->offset + size <= current->size)
    {
        result = (void*)((char*)current->basic + current->offset);
        current->offset += size;
    }
    else
    {
        current = _BlockCreate(pool->blocksize);
        result = (void*)((char*)current->basic);
        current->offset = size;
        pool->current->next = current;
        pool->current = current;
    }
    return result;
}
void* GLMemoryPoolAllocInBlock(GLMemoryPool* pool, size_t size)
{
    Block* current;
    void* result;
    GLASSERT(NULL!=pool);
    GLASSERT(0 < size);
    GLASSERT(NULL!=pool->current);
    GLASSERT(size < pool->blocksize);
    size = ALIGN_UP(size, 8);
    current = pool->current;
    if (current->offset + size <= current->size)
    {
        result = (void*)((char*)current->basic + current->offset);
        current->offset += size;
        return result;
    }
    return NULL;
}
#undef ALIGN_UP
