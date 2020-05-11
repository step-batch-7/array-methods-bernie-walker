#include "test.h"
#include "../array.h"
#include "../array_void.h"
#include "../aider.h"

typedef Bool (*Comparator)(Object, Object);

void destroy_all_void_arrays(size_t length, ArrayVoid_ptr void_arrays[length])
{
  for (size_t i = 0; i < length; i++)
  {
    destroy_void_array(void_arrays[i]);
  }
}

Bool are_chars_equal(Object char1, Object char2)
{
  return *(char *)char1 == *(char *)char2;
}

Bool are_numbers_equal(Object num1, Object num2)
{
  return *(int *)num1 == *(int *)num2;
}

Bool compare_void_arrays(ArrayVoid_ptr array_void1, ArrayVoid_ptr array_void2, Comparator equality_checker)
{
  if (array_void1->length != array_void2->length)
  {
    return False;
  }

  for (size_t i = 0; i < array_void1->length; i++)
  {
    if (!equality_checker(array_void1->array[i], array_void2->array[i]))
    {
      return False;
    }
  }

  return True;
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

void test_reduce_void(void)
{
  ArrayVoid_ptr array_void = get_default_void_array(4, generate_int);
  Object actual = reduce_void(array_void, malloc(sizeof(int)), add_numbers);
  assert_strict_equal("Should add all the numbers in the list", *(int *)actual, 6);
  free(actual);

  array_void = resize_void_array(array_void, 0);
  *(int *)actual = 9;

  actual = reduce_void(array_void, actual, add_numbers);
  assert_strict_equal("Should return the initial value when the array is empty", *(int *)actual, 9);

  free(array_void);
  free(actual);
}

void test_filter_void(void)
{
  ArrayVoid_ptr array_void = get_default_void_array(4, generate_int);
  ArrayVoid_ptr actual = filter_void(array_void, is_num_even);
  ArrayVoid_ptr expected = init_array_void(2);
  expected->array[0] = generate_int(0);
  expected->array[1] = generate_int(2);

  Bool are_equal = compare_void_arrays(actual, expected, are_numbers_equal);
  assert_strict_equal("Should filter all the even numbers", are_equal, True);
  ArrayVoid_ptr void_arrays1[] = {array_void, expected};
  destroy_all_void_arrays(2, void_arrays1);

  array_void = get_default_void_array(5, generate_char);
  actual = filter_void(array_void, is_vowel);
  expected = init_array_void(2);
  expected->array[0] = generate_char(0);
  expected->array[1] = generate_char(4);

  are_equal = compare_void_arrays(actual, expected, are_chars_equal);
  assert_strict_equal("Should filter out all the vowels", are_equal, True);
  ArrayVoid_ptr void_arrays2[] = {array_void, expected};
  destroy_all_void_arrays(2, void_arrays2);
}

void test_map_void(void)
{
  ArrayVoid_ptr array_void = get_default_void_array(4, generate_int);
  ArrayVoid_ptr actual = map_void(array_void, inc_num);
  ArrayVoid_ptr expected = init_array_void(4);
  for (size_t i = 0; i < 4; i++)
  {
    expected->array[i] = generate_int(i + 1);
  }

  Bool are_equal = compare_void_arrays(actual, expected, are_numbers_equal);
  assert_strict_equal("Should increment all the numbers in void array", are_equal, True);
  ArrayVoid_ptr void_arrays1[] = {array_void, actual, expected};
  destroy_all_void_arrays(3, void_arrays1);

  array_void = get_default_void_array(4, generate_char);
  actual = map_void(array_void, get_lower_case);
  expected = init_array_void(4);
  for (size_t i = 0; i < 4; i++)
  {
    expected->array[i] = generate_char(i + 22);
  }

  are_equal = compare_void_arrays(actual, expected, are_chars_equal);
  assert_strict_equal("Should change all the letters to lower case", are_equal, True);
  ArrayVoid_ptr void_arrays2[] = {array_void, actual, expected};
  destroy_all_void_arrays(3, void_arrays2);
}

void test_reduce(void)
{
  Array_ptr test_array = get_default_array(4);
  int total = reduce(test_array, 0, add);
  assert_strict_equal("Should get the sum of all the elements in the array", total, 6);
  test_array = resize_array(test_array, 0);
  assert_strict_equal("Should return the init value when for an empty array", reduce(test_array, 0, add), 0);
}

void test_filter(void)
{
  Array_ptr expected = init_array(2);
  expected->array[0] = 0;
  expected->array[1] = 2;
  Array_ptr test_array = get_default_array(4);
  Array_ptr filtered = filter(test_array, is_even);
  assert_strict_equal("Should filter out all the non even elements", are_arrays_equal(filtered, expected), True);
  test_array = resize_array(test_array, 0);
  Array_ptr result = filter(test_array, is_even);
  assert_strict_equal("Should return a new empty array when the src array is empty", (result != test_array), 1);
  assert_strict_equal("The length of the resulting array should be 0 when filtering an empty array", result->length, 0);
}

void test_map(void)
{
  Array_ptr expected = init_array(4);
  for (size_t i = 0; i < 4; i++)
  {
    expected->array[i] = add_one(i);
  }
  Array_ptr test_array = get_default_array(4);
  Array_ptr squared = map(test_array, add_one);
  assert_strict_equal("Should square the elements of the array", are_arrays_equal(squared, expected), True);
  test_array = resize_array(test_array, 0);
  Array_ptr result = map(test_array, add_one);
  assert_strict_equal("Should return a new empty array when the src array is empty", (result != test_array), 1);
  assert_strict_equal("The length of the resulting array should be 0 when mapping an empty array", result->length, 0);
}

int main(void)
{
  exec_test_suite("map", test_map);
  exec_test_suite("filter", test_filter);
  exec_test_suite("reduce", test_reduce);
  exec_test_suite("map_void", test_map_void);
  exec_test_suite("filter_void", test_filter_void);
  exec_test_suite("reduce_void", test_reduce_void);
  print_report();
  return 0;
}