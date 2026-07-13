#include <stdio.h>
#include <time.h>
#include <limits.h>

time_t max_t()
{
  time_t low = 0, high = LONG_LONG_MAX;
  time_t result = 0;

  while (low <= high)
  {
    time_t mid = low + (high - low) / 2;
    if (ctime(&mid) != NULL)
    {
      result = mid;
      low = mid + 1;
    }
    else
    {
      high = mid - 1;
    }
  }

  return result;
}
