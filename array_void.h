#ifndef __ARRAY_VOID_H
#define __ARRAY_VOID_H

#include "array.h"

typedef void *Object;

typedef Object (*MapperVoid)(Object);
typedef Bool (*PredicateVoid)(Object);
typedef Object (*ReducerVoid)(Object, Object);
typedef void (*Printer)(Object);

typedef struct
{
  Object *array;
  int length;
} ArrayVoid;

typedef ArrayVoid *ArrayVoid_ptr;

ArrayVoid_ptr init_array_void(size_t);
void display_array_void(char[], ArrayVoid_ptr, Printer);
ArrayVoid_ptr resize_void_array(ArrayVoid_ptr, size_t);

ArrayVoid_ptr map_void(ArrayVoid_ptr, MapperVoid);
ArrayVoid_ptr filter_void(ArrayVoid_ptr, PredicateVoid);
Object reduce_void(ArrayVoid_ptr, Object, ReducerVoid);

void destroy_void_array(ArrayVoid_ptr);

#endif