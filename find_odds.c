#include <stdlib.h>

int find_range(size_t length, const int array[length], int *max)
{
  int min = array[0];
  
  for (size_t i = 0; i < length; i++) 
  {
    if (array[i] > *max) *max = array[i];
    else if (array[i] < min) min = array[i];
  }
  
  int range = *max - min;
  return range > *max ? range : *max;
}

void fill_memo(size_t length, const int array[length], int range, int *memo, int *has_negative)
{
    for (size_t i = 0; i < length; i++)
  {
    if (array[i] >= 0) memo[array[i]]++;
    else 
    {
      *has_negative = 1;
      memo[range + 1 + array[i]]++;
    }
  }
}

int actually_find_odd(int range, int *memo, int has_negative, int max)
{
  for (int i = 0; i <= range; i++) 
  {
    if (memo[i] % 2)
    {
      if (has_negative)
      {
        if (i > max)
        {
          return i - range - 1;
        }
        else return i;
      }
      else return i;
    return -1;
    }
  }
}

int find_odd (size_t length, const int array[length])
{
  if (length == 1) return array[0];
  
  int has_negative = 0;
  int max = array[0];
  int range = find_range(length, array, &max);
  
  // create a dynamically allocated array, length is array's min - max values
  int *memo = (int *)calloc(range + 1, sizeof(int));
  
  // increments relative locations in dynamic array (ex. array[0] = 2 so memo[2]++)
  fill_memo(length, array, range, memo, &has_negative);
  
  // search memo for an odd value and return the index
  int output = actually_find_odd(range, memo, has_negative, max);

  // don't forget to free
  free(memo);
  return output;
}
