#include "test.h"
#include "../array.h"

Array_ptr get_default(void)
{
  Array_ptr default_array = init_array(4);
  for (size_t i = 0; i < 4; i++)
  {
    default_array->array[i] = i;
  }
  return default_array;
}

Bool are_arrays_equal(Array_ptr int_array1, Array_ptr int_array2)
{
  if (int_array1->length != int_array2->length)
  {
    return False;
  }

  for (size_t i = 0; i < int_array1->length; i++)
  {
    if (int_array1->array[i] != int_array2->array[i])
    {
      return False;
    }
  }

  return True;
}

int add(int num1, int num2)
{
  return num1 + num2;
}

void test_reduce(void)
{
  Array_ptr test_array = get_default();
  int total = reduce(test_array, 0, add);
  assert_strict_equal("Should get the sum of all the elements in the array", total, 6);
  test_array = resize_array(test_array, 0);
  assert_strict_equal("Should return the init value when for an empty array", reduce(test_array, 0, add), 0);
}

Bool is_even(int num)
{
  return (num & 1) == 0;
}

void test_filter(void)
{
  Array_ptr expected = init_array(2);
  expected->array[0] = 0;
  expected->array[1] = 2;
  Array_ptr test_array = get_default();
  Array_ptr filtered = filter(test_array, is_even);
  assert_strict_equal("Should filter out all the non even elements", are_arrays_equal(filtered, expected), True);
  test_array = resize_array(test_array, 0);
  Array_ptr result = filter(test_array, is_even);
  assert_strict_equal("Should return a new empty array when the src array is empty", (result != test_array), 1);
  assert_strict_equal("The length of the resulting array should be 0 when filtering an empty array", result->length, 0);
}

int get_square(int num)
{
  return num * num;
}

void test_map(void)
{
  Array_ptr expected = init_array(4);
  for (size_t i = 0; i < 4; i++)
  {
    expected->array[i] = get_square(i);
  }
  Array_ptr test_array = get_default();
  Array_ptr squared = map(test_array, get_square);
  assert_strict_equal("Should square the elements of the array", are_arrays_equal(squared, expected), True);
  test_array = resize_array(test_array, 0);
  Array_ptr result = map(test_array, get_square);
  assert_strict_equal("Should return a new empty array when the src array is empty", (result != test_array), 1);
  assert_strict_equal("The length of the resulting array should be 0 when mapping an empty array", result->length, 0);
}

int main(void)
{
  exec_test_suite("map", test_map);
  exec_test_suite("filter", test_filter);
  exec_test_suite("reduce", test_reduce);
  print_report();
  return 0;
}