#include <stdio.h>
#include <stdlib.h>

#ifndef __ARRAY_H
#define __ARRAY_H
typedef enum
{
  False,
  True
} Bool;

typedef int (*Mapper)(int);
typedef Bool (*Predicate)(int);
typedef int (*Reducer)(int, int);

typedef int *Int_ptr;

typedef struct
{
  Int_ptr array;
  int length;
} Array;

typedef Array *Array_ptr;

Array_ptr init_array(size_t);
Array_ptr resize_array(Array_ptr, size_t);
void print_array(char[], Array_ptr);

Array_ptr map(Array_ptr, Mapper);
Array_ptr filter(Array_ptr, Predicate);
int reduce(Array_ptr, int, Reducer);

void destroy_array(Array_ptr);
#endif
