#include <stdio.h>
#include "array.h"

int add(int num1, int num2)
{
  return num1 + num2;
}

Bool is_even(int num)
{
  return (num & 1) == 0;
}

int add_one(int num)
{
  return num + 1;
}

Array_ptr get_default_array(size_t length)
{
  Array_ptr int_array = init_array(length);
  for (size_t i = 0; i < length; i++)
  {
    int_array->array[i] = i;
  }
  return int_array;
}

int main(void)
{
  Array_ptr int_array = get_default_array(6);

  print_array("Original array", int_array);
  print_array("Result of Map", map(int_array, add_one));
  print_array("Result of Filter", filter(int_array, is_even));
  printf("Result of Reduce\n%d\n", reduce(int_array, 0, add));

  destroy_array(int_array);
  return 0;
}