#include <stdio.h>
#include "array.h"
#include "aider.h"

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