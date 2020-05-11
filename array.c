#include "array.h"

Array_ptr init_array(size_t length)
{
  Array_ptr int_array = malloc(sizeof(Array));
  int_array->length = length;
  int_array->array = malloc(sizeof(int) * length);
  return int_array;
}

Array_ptr resize_array(Array_ptr int_array, size_t length)
{
  int_array->length = length;
  Int_ptr new_array_ptr = realloc(int_array->array, int_array->length * sizeof(int));

  if (new_array_ptr == NULL)
  {
    printf("Insufficient memory\n");
    exit(1);
  }

  int_array->array = new_array_ptr;
  return int_array;
}

void print_array(char message[], Array_ptr int_array)
{
  printf("%s\n", message);
  for (size_t i = 0; i < int_array->length; i++)
  {
    printf("%d ", int_array->array[i]);
  }
  printf("\n");
}

Array_ptr map(Array_ptr src, Mapper mapper)
{
  Array_ptr result = init_array(src->length);

  for (size_t i = 0; i < src->length; i++)
  {
    result->array[i] = mapper(src->array[i]);
  }

  return result;
}

Array_ptr filter(Array_ptr src, Predicate predicate)
{
  Array_ptr result = init_array(src->length);
  if (src->length == 0)
  {
    return result;
  }

  int result_index = 0;
  for (size_t i = 0; i < src->length; i++)
  {
    if (predicate(src->array[i]) == True)
    {
      result->array[result_index] = src->array[i];
      ++result_index;
    }
  }

  return resize_array(result, result_index);
}

int reduce(Array_ptr src, int init, Reducer reducer)
{
  for (size_t i = 0; i < src->length; i++)
  {
    init = reducer(init, src->array[i]);
  }

  return init;
}

void destroy_array(Array_ptr int_array)
{
  free(int_array->array);
  free(int_array);
}
