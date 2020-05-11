#include "aider.h"
#include "array_void.h"

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

Object generate_int(int value)
{
  Object int_value = malloc(sizeof(int));
  *(int *)int_value = value;
  return int_value;
}

Object generate_char(int value)
{
  Object char_value = malloc(1);
  *(char *)char_value = 65 + value;
  return char_value;
}

ArrayVoid_ptr get_default_void_array(size_t length, Genearator value_generator)
{
  ArrayVoid_ptr array_void = init_array_void(length);

  for (size_t i = 0; i < array_void->length; i++)
  {
    array_void->array[i] = value_generator(i);
  }

  return array_void;
}

Object inc_num(Object num)
{
  Object result = malloc(sizeof(int));
  *(int *)result = *(int *)num + 1;
  return result;
}

Object get_lower_case(Object alphabet)
{
  Object result = malloc(sizeof(char));
  *(char *)result = *(char *)alphabet + 22;
  return result;
}

Bool is_num_even(Object num)
{
  return is_even(*(int *)num);
}

Bool is_vowel(Object alphabet)
{
  char refernce[] = "aeiouAEIOU";
  for (size_t i = 0; i < 10; i++)
  {
    if (refernce[i] == *(char *)alphabet)
    {
      return True;
    }
  }
  return False;
}

Object add_numbers(Object num1, Object num2)
{
  *(int *)num1 = *(int *)num1 + *(int *)num2;
  return num1;
}