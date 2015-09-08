#include <stdio.h>

int main()
{
  char a[1024];
  int i = 0;

  printf("Input:\n");
  do {
    scanf("%d", a + i);
  } while (a[i++] != 42);

  printf("\nOutput:\n");
  i = 0;
  while( a[i] != 42 )
    printf("%d\n", a[i++]);
  
  return 0;
}
