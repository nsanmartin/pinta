#ifndef __H_YRR_TEST_H_
#define __H_YRR_TEST_H_

#include <stddef.h>

void* yrr_test_malloc(size_t s);
void* yrr_test_realloc(void* ptr, size_t s);
void yrr_test_free(void* ptr);
#endif

