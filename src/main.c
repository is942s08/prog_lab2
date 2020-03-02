#include <stdio.h>
#include <stdint.h>
#include <ctest.h>
#include "IntVector.h"

#define CTEST_MAIN
#define CTEST_SEGFAULT

int main(int argc, char const *argv[])
{
	return ctest_main(argc, argv);
}

CTEST(int_vector_test, copy)
{
	// Given
	const size_t capacity = 10;
	IntVector* vec_orig = int_vector_new(capacity);
	for (int i = 0; i < 10; i++) {
		int_vector_push_back(vec_orig, i);
	}

	// When
	IntVector* vec_new = int_vector_copy(vec_orig);

	// Then
	for (int i = 0; i < 10; i++) {
		ASSERT_EQUAL(i, int_vector_get_item(vec_new, i));
	}
	int_vector_free(vec_orig);
	int_vector_free(vec_new);
}

CTEST(int_vector_test, push_back)
{
	// Given
	const size_t capacity = 1;
	IntVector* vec = int_vector_new(capacity);

	// When
	int_vector_push_back(vec, 10);

	// Then
	ASSERT_EQUAL(10, int_vector_get_item(vec, 0));
	ASSERT_EQUAL(1, int_vector_get_size(vec));
	int_vector_free(vec);
}

CTEST(int_vector_test, push_back_overcap)
{
	// Given
	const size_t capacity = 1;
	IntVector* vec = int_vector_new(capacity);

	// When
	int_vector_push_back(vec, 10);
	int_vector_push_back(vec, 20);

	// Then
	ASSERT_EQUAL(10, int_vector_get_item(vec, 0));
	ASSERT_EQUAL(20, int_vector_get_item(vec, 1));
	ASSERT_EQUAL(2, int_vector_get_size(vec));
	ASSERT_EQUAL(2, int_vector_get_capacity(vec));
	int_vector_free(vec);
}

CTEST(int_vector_test, pop_back)
{
	// Given
	const size_t capacity = 1;
	IntVector* vec = int_vector_new(capacity);
	int_vector_push_back(vec, 10);

	// When
	int_vector_pop_back(vec);

	// Then
	ASSERT_EQUAL(0, int_vector_get_size(vec));
	int_vector_free(vec);
}

CTEST(int_vector_test, pop_back_less_than_zero)
{
	// Given
	const size_t capacity = 1;
	IntVector* vec = int_vector_new(capacity);

	// When
	int_vector_pop_back(vec);

	// Then
	ASSERT_EQUAL(0, int_vector_get_size(vec));
	int_vector_free(vec);
}

CTEST(int_vector_test, shrink_to_fit)
{
	// Given
	const size_t capacity = 10;
	IntVector* vec = int_vector_new(capacity);
	int_vector_push_back(vec, 10);

	// When
	int_vector_shrink_to_fit(vec);

	// Then
	ASSERT_EQUAL(1, int_vector_get_capacity(vec));
	int_vector_free(vec);
}

CTEST(int_vector_test, resize_less_then_original)
{
	// Given
	const size_t capacity = 10;
	IntVector* vec = int_vector_new(capacity);
	for (int i = 0; i < 7; i++) {
		int_vector_push_back(vec, i);
	}

	// When
	const int result = int_vector_resize(vec, 5);

	// Then
	ASSERT_EQUAL(5, int_vector_get_size(vec));
	ASSERT_EQUAL(5, int_vector_get_capacity(vec));
	ASSERT_EQUAL(0, result);
	int_vector_free(vec);
}

CTEST(int_vector_test, resize_more_then_original)
{
	// Given
	const size_t capacity = 10;
	IntVector* vec = int_vector_new(capacity);
	for (int i = 0; i < 5; i++) {
		int_vector_push_back(vec, i);
	}

	// When
	const int result = int_vector_resize(vec, 10);

	// Then
	ASSERT_EQUAL(10, int_vector_get_size(vec));
	ASSERT_EQUAL(10, int_vector_get_capacity(vec));
	for (int i = 0; i < 5; i++) {
		ASSERT_EQUAL(i, int_vector_get_item(vec, i));
	}
	for (int i = 5; i < 10; i++) {
		ASSERT_EQUAL(0, int_vector_get_item(vec, i));
	}
	ASSERT_EQUAL(0, result);
	int_vector_free(vec);
}

CTEST(int_vector_test, resize_more_then_original_overcap)
{
	// Given
	const size_t capacity = 10;
	IntVector* vec = int_vector_new(capacity);
	for (int i = 0; i < 5; i++) {
		int_vector_push_back(vec, i);
	}

	// When
	const int result = int_vector_resize(vec, 15);

	// Then
	ASSERT_EQUAL(15, int_vector_get_size(vec));
	ASSERT_EQUAL(30, int_vector_get_capacity(vec));
	for (int i = 0; i < 5; i++) {
		ASSERT_EQUAL(i, int_vector_get_item(vec, i));
	}
	for (int i = 5; i < 15; i++) {
		ASSERT_EQUAL(0, int_vector_get_item(vec, i));
	}
	ASSERT_EQUAL(0, result);
	int_vector_free(vec);
}

CTEST(int_vector_test, reserve_less_then_original)
{
	// Given
	const size_t capacity = 10;
	IntVector* vec = int_vector_new(capacity);

	// When
	const int result = int_vector_reserve(vec, 5);

	// Then
	ASSERT_EQUAL(10, int_vector_get_capacity(vec));
	ASSERT_EQUAL(-1, result);
	int_vector_free(vec);
}

CTEST(int_vector_test, reserve_more_then_original)
{
	// Given
	const size_t capacity = 10;
	IntVector* vec = int_vector_new(capacity);

	// When
	const int result = int_vector_reserve(vec, 15);

	// Then
	ASSERT_EQUAL(15, int_vector_get_capacity(vec));
	ASSERT_EQUAL(0, result);
	int_vector_free(vec);
}

CTEST(int_vector_test, reserve_allocation_error)
{
	// Given
	const size_t capacity = 10;
	const size_t max = SIZE_MAX;
	IntVector* vec = int_vector_new(capacity);

	// When
	const int result = int_vector_reserve(vec, max);

	// Then
	ASSERT_EQUAL(10, int_vector_get_capacity(vec));
	ASSERT_EQUAL(-1, result);
	int_vector_free(vec);
}