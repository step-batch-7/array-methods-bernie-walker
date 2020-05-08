#include "helper.h"

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
