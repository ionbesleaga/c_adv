#include <stdio.h>
#include "snippets/max_time.h"

int main()
{
  time_t t = max_t();

  char *s = ctime(&t);
  printf("%s\n", s);
  return 0;

  printf("\n\n");
}
