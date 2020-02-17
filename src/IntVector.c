#include <stdlib.h>

typedef struct
{
    int* data;
    size_t size;
    size_t cap;
} IntVector;

IntVector* int_vector_new(size_t cap);
IntVector* int_vector_copy(IntVector* v);
void int_vector_free(IntVector* v);
int int_vector_get_item(const IntVector* v, int index);
void int_vector_set_item(IntVector* v, int index, int item);
size_t int_vector_get_size(const IntVector* v);
size_t int_vector_get_capacity(const IntVector* v);
int int_vector_push_back(IntVector* v, int item);
void int_vector_pop_back(IntVector* v);
int int_vector_shrink_to_fit(IntVector* v);
int int_vector_resize(IntVector* v, size_t new_size);
int int_vector_reserve(IntVector* v, size_t new_cap);


IntVector* int_vector_new(size_t cap)
{
    IntVector* v = malloc(sizeof(IntVector));
    v->cap = cap;
    v->size = 0;
    v->data = malloc(cap * sizeof(int));
    
    if (v->data == NULL) {
	return NULL;
    }
    
    return v;
}

IntVector* int_vector_copy(IntVector* v)
{
    IntVector* new_v = malloc(sizeof(IntVector));
    new_v->cap = v->cap;
    new_v->size = v->size;
    new_v->data = malloc(cap * sizeof(int));
    
    for (int i = 0; n < new_v->size; i++) {
	new_v->data[i] = v->data[i];
    }
    
    if (new_v->data == NULL) {
	return NULL;
    }
    
    return new_v;
}

