#include <stdlib.h>
#include "IntVector.h"

IntVector* int_vector_new(size_t cap)
{
	IntVector* v = (IntVector*)malloc(sizeof(IntVector));

	if (v == NULL) {
		return NULL;
	}

	v->cap = cap;
	v->size = 0;
	v->data = (int*)malloc(cap * sizeof(int));
	
	if (v->data == NULL) {
		free(v);
		return NULL;
	}
	
	return v;
}

IntVector* int_vector_copy(IntVector* v)
{
	IntVector* new_v = int_vector_new(v->cap);
	new_v->size = v->size;
	
	for (int i = 0; i < new_v->size; i++) {
		new_v->data[i] = v->data[i];
	}

	return new_v;
}

void int_vector_free(IntVector* v)
{
	free(v->data);
	free(v);
}

int int_vector_get_item(const IntVector* v, int index)
{
	return v->data[index];
}

void int_vector_set_item(IntVector* v, int index, int item)
{
	v->data[index] = item;
}

size_t int_vector_get_size(const IntVector* v)
{
	return v->size;
}

size_t int_vector_get_capacity(const IntVector* v)
{
	return v->cap;
}

int int_vector_push_back(IntVector* v, int item)
{
	int result = 0;

	if (v->size + 1 > v->cap) {
		result = int_vector_reserve(v, v->cap * 2);
		if (result) {
			return -1;
		}
	}

	v->data[v->size] = item;
	v->size++;

	return 0;
}

void int_vector_pop_back(IntVector* v)
{
	if (v->size != 0) {
		v->size--;
	}
}

int int_vector_shrink_to_fit(IntVector* v)
{
	int* new_data_ptr = (int*)realloc(v->data, v->size * sizeof(int*));
	if (new_data_ptr == NULL) {
		return -1;
	}

	v->cap = v->size;
	v->data = new_data_ptr;
	return 0;
}

int int_vector_resize(IntVector* v, size_t new_size)
{
	if (new_size < v->size) {
		v->size = new_size;
		return int_vector_shrink_to_fit(v);
	}
	
	if (new_size > v->size) {
		if (new_size > v->cap) {
			int result = int_vector_reserve(v, new_size * 2);
			if (result == -1) {
				return -1;
			}
		}

		for (int i = v->size; i < new_size; i++) {
			v->data[i] = 0;
		}

		v->size = new_size;
		return 0;
	}

	return 0;
}

int int_vector_reserve(IntVector* v, size_t new_cap)
{
	if (new_cap > v->cap) {
		int* new_data_ptr = (int*)realloc(v->data, new_cap * sizeof(int*));
		if (new_data_ptr == NULL) {
			return -1;
		}

		v->cap = new_cap;
		v->data = new_data_ptr;
		return 0;
	}

	return -1;
}