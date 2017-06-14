#ifndef VECTOR_H
#define VECTOR_H
//-------------------------------------------------------
// Data structure to hold instruction's list:
// Dynamic Array ( aka Vector )

#include "mips_definitions.h"
#define _TYPE_ instruction

#define VECTOR_INITIAL_CAPACITY 256

typedef struct {
  int size;      			// slots used so far
  int capacity;  			// total available slots
  _TYPE_ * data;      // array we're storing
} Vector;

void vector_init(Vector *vector);

void vector_append(Vector *vector, _TYPE_ value);

void vector_free_data(Vector *vector);


//-------------------------------------------------------
#endif