#pragma once

typedef struct linearAllocator {
    unsigned long long size;
    unsigned long long alloced;
    void* memory;
} linearAllocator;

void linearAllocCreate(unsigned long long size, linearAllocator* outLinearAlloc);
void* linearAllocAllocate(linearAllocator* linearAlloc, unsigned long long size);
void linearAllocReset(linearAllocator* linearAlloc);
void linearAllocDestroy(linearAllocator* linearAlloc);

#ifdef LINEAR_ALLOCATOR_IMPLEMENTION 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void linearAllocCreate(unsigned long long size, linearAllocator* outLinearAlloc) {
    if (outLinearAlloc) {
        outLinearAlloc->memory = malloc(size);
        outLinearAlloc->size = size;
        outLinearAlloc->alloced = 0;
        return;
    }

    fprintf(stderr, "linearAllocCreate was not given an outLinearAlloc\n");
}

void* linearAllocAllocate(linearAllocator* linearAlloc, unsigned long long size) {
    if (linearAlloc && linearAlloc->memory) {
        if (linearAlloc->alloced + size > linearAlloc->size) {
            unsigned long long remainingSpace =
                linearAlloc->size - linearAlloc->alloced;
            fprintf(stderr,
                    "Linear allocator out of memory. Remaining space: %lluB\n",
                    remainingSpace);
            return 0;
        }
        void* p = ((unsigned char*)linearAlloc->memory) + linearAlloc->alloced;
        linearAlloc->alloced += size;
        return p;
    }
    fprintf(stderr, "Linear allocator not allocated or inited\n");
    return 0;
}

void linearAllocReset(linearAllocator* linearAlloc) {
    if (linearAlloc && linearAlloc->memory) {
        memset(linearAlloc->memory, 0, linearAlloc->size);
        linearAlloc->alloced = 0;
    }
}

void linearAllocDestroy(linearAllocator* linearAlloc) {
    if (linearAlloc && linearAlloc->memory) {
        free(linearAlloc->memory);
        linearAlloc->memory = 0;
        linearAlloc->size = 0;
        linearAlloc->alloced = 0;
    }
}
#endif
