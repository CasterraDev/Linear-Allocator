#include "linearallocator.h"

#include "expect.h"

#define LINEAR_ALLOCATOR_IMPLEMENTION

unsigned char linearAllocCreateDestory(void) {
    linearAllocator a;
    linearAllocCreate(sizeof(unsigned long long), &a);
    expect(sizeof(unsigned long long), a.size);
    expectNot(0, a.memory);
    expect(0, a.alloced);
    linearAllocDestroy(&a);
    expect(0, a.alloced);
    expect(0, a.memory);
    expect(0, a.size);
    return 1;
}

unsigned char linearAllocAllSpace(void) {
    linearAllocator alloc;
    linearAllocCreate(sizeof(unsigned long long), &alloc);

    // Single allocation.
    void* block = linearAllocAllocate(&alloc, sizeof(unsigned long long));

    // Validate it
    expect(sizeof(unsigned long long), alloc.alloced);
    expectNot(0, block);

    linearAllocDestroy(&alloc);
    expect(0, alloc.alloced);
    expect(0, alloc.memory);
    expect(0, alloc.size);

    return 1;
}

unsigned char linearAllocMultipleAllSpace(void) {
    linearAllocator alloc;
    linearAllocCreate(sizeof(unsigned long long) * 3, &alloc);
    expect(sizeof(unsigned long long) * 3, alloc.size);

    void* block = linearAllocAllocate(&alloc, sizeof(unsigned long long));
    expect(sizeof(unsigned long long), alloc.alloced);
    expectNot(0, block);
    void* block2 = linearAllocAllocate(&alloc, sizeof(unsigned long long));
    expect(sizeof(unsigned long long) * 2, alloc.alloced);
    expectNot(0, block2);
    void* block3 = linearAllocAllocate(&alloc, sizeof(unsigned long long));
    expect(sizeof(unsigned long long) * 3, alloc.alloced);
    expectNot(0, block3);

    linearAllocDestroy(&alloc);
    expect(0, alloc.alloced);
    expect(0, alloc.memory);
    expect(0, alloc.size);

    return 1;
}

unsigned char linearAllocOverflow(void) {
    linearAllocator alloc;
    linearAllocCreate(sizeof(unsigned long long), &alloc);
    expect(sizeof(unsigned long long), alloc.size);

    // Single allocation.
    void* block = linearAllocAllocate(&alloc, sizeof(unsigned long long));
    expect(sizeof(unsigned long long), alloc.alloced);
    printf("There should be an error message telling you that there is no "
           "remaining space in the allocator. This error msg is intentional "
           "for the test.\n");
    void* block2 = linearAllocAllocate(&alloc, sizeof(unsigned long long));

    linearAllocDestroy(&alloc);

    return 1;
}

unsigned char linearAllocAllocReset(void) {
    linearAllocator alloc;
    linearAllocCreate(sizeof(unsigned long long), &alloc);

    // Single allocation.
    void* block = linearAllocAllocate(&alloc, sizeof(unsigned long long));

    // Validate it
    expect(sizeof(unsigned long long), alloc.alloced);
    expectNot(0, block);

    linearAllocReset(&alloc);
    expect(0, alloc.alloced);
    expectNot(0, alloc.memory);
    expect(sizeof(unsigned long long), alloc.size);

    void* block2 = linearAllocAllocate(&alloc, 2);
    expect(2, alloc.alloced);
    expectNot(0, block2);

    linearAllocDestroy(&alloc);

    return 1;
}

void linearAllocRegisterTests(void) {
    linearAllocCreateDestory();
    linearAllocAllSpace();
    linearAllocMultipleAllSpace();
    linearAllocOverflow();
    linearAllocAllocReset();
}

int main(void) {
    linearAllocRegisterTests();
    return 0;
}
