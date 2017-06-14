#include <stdio.h>

#define div __not_div__
#include <stdlib.h>
#undef div

#include "vector.h"

void vector_init(Vector *vector) {
	// initialize size and capacity
	vector->size = 0;
	vector->capacity = VECTOR_INITIAL_CAPACITY;

	// allocate memory for vector->data
	vector->data = malloc(sizeof(_TYPE_) * vector->capacity);
}

void _vector_expand(Vector *vector) {
    vector->capacity *= 2;
    vector->data = realloc(vector->data, sizeof(_TYPE_) * vector->capacity);
}

void vector_append(Vector *vector, _TYPE_ value) {
	// make sure there's room to expand into
	if (vector->size >= vector->capacity)
		_vector_expand(vector);	

	// append the value and increment vector->size
	vector->data[vector->size++] = value;
}

void vector_free_data(Vector *vector) {
  free(vector->data);
}