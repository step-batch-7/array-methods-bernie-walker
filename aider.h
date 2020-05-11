#include "array.h"
#include "array_void.h"

#ifndef __AIDER_H_
#define __AIDER_H_

typedef Object (*Genearator)(int);

int add(int, int);

Bool is_even(int);

int add_one(int);

Array_ptr get_default_array(size_t);

Object generate_int(int);

Object generate_char(int);

ArrayVoid_ptr get_default_void_array(size_t, Genearator);

Object inc_num(Object);

Object get_lower_case(Object);

Bool is_num_even(Object);

#endif // !__AIDER_H_
