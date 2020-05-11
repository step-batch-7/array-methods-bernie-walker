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

ArrayVoid_ptr resize_void_array(ArrayVoid_ptr void_array, size_t length)
{
  void_array->length = length;
  Object *new_array_ptr = realloc(void_array->array, (length * sizeof(Object)));

  if (new_array_ptr == NULL)
  {
    printf("Insufficient memory\n");
    exit(1);
  }

  void_array->array = new_array_ptr;
  return void_array;
}

ArrayVoid_ptr filter_void(ArrayVoid_ptr src, PredicateVoid predicate)
{
  ArrayVoid_ptr filter_result = init_array_void(src->length);
  if (src->length == 0)
  {
    return filter_result;
  }

  int result_index = 0;
  for (size_t i = 0; i < src->length; i++)
  {
    if (predicate(src->array[i]))
    {
      filter_result->array[result_index] = src->array[i];
      ++result_index;
    }
  }

  return resize_void_array(filter_result, result_index);
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