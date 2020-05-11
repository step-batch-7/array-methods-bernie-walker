#include "array_void.h"

ArrayVoid_ptr init_array_void(size_t length)
{
  ArrayVoid_ptr array_void = malloc(sizeof(ArrayVoid));
  array_void->length = length;
  array_void->array = malloc(sizeof(Object) * length);
  return array_void;
}

void display_void_array(char message[], ArrayVoid_ptr array_void, Printer display_function)
{
  printf("%s\n", message);
  for (size_t i = 0; i < array_void->length; i++)
  {
    display_function(array_void->array[i]);
  }
  printf("\n");
}

ArrayVoid_ptr map_void(ArrayVoid_ptr src, MapperVoid mapper)
{
  ArrayVoid_ptr map_result = init_array_void(src->length);

  for (size_t i = 0; i < src->length; i++)
  {
    map_result->array[i] = mapper(src->array[i]);
  }

  return map_result;
}

void destroy_void_array(ArrayVoid_ptr array_void)
{
  for (size_t i = 0; i < array_void->length; i++)
  {
    free(array_void->array[i]);
  }
  free(array_void->array);
  free(array_void);
}