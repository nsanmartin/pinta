#include <stdio.h>
#include <stdlib.h>

#include <test.h>

#define MALLOC_TIMES 3

int yrr_malloc_times = MALLOC_TIMES;
int yrr_malloc_calls = 0;
int yrr_free_calls = 0;

void* yrr_test_malloc(size_t size) {
    if (yrr_malloc_times > 0) {
        printf("malloc calls: %d. Remaining: %d\n", ++yrr_malloc_calls, --yrr_malloc_times);
        return malloc(size);
    }
    return NULL;
}

void* yrr_test_realloc(void* ptr, size_t size) {
    if (yrr_malloc_times > 0) {
        printf("realloc call. Remaining: %d\n", yrr_malloc_times--);
        return realloc(ptr, size);
    }
    return NULL;
}

void yrr_test_free(void* ptr) {
    ++yrr_free_calls;
    printf("free calls: %d (malloc-free: %d)\n", yrr_free_calls, yrr_malloc_calls - yrr_free_calls);
    free(ptr);
}
