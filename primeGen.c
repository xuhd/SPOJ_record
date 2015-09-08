#include <stdio.h>
#include <math.h>

int is_prime(int number)
{
  int i;

  if(number<2)
    return 0;
  if(number==2)
    return 1;
  if(number%2==0)
    return 0;

  for(i=3;i<=sqrt(number);i += 2) {
    if(number%i==0)
    return 0;
  }
  return 1;
}

int main(void)
{
  int i, k;
  int t;
  int m[10], n[10];
  
  scanf("%d", &t);

  if(t <=0 || t > 10)
    return -1;

  for(i = 0; i < t; i++)
    scanf("%d %d", m+i, n+i);

  for(i = 0; i < t; i++) {
    for(k = m[i]; k <= n[i]; k++) {
      if( is_prime(k) )
	printf("%d\n", k);
    }
    printf("\n");
  }
  return 0;
}
