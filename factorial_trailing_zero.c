#include <stdio.h>

unsigned fctrl_tz(unsigned n)
{
  unsigned q, d = 5, cnt = 0;
  while( q = n/d ) {cnt += q; d *= 5;}
  return cnt;
}

int main(void)
{
  int i, k;
  int t;
  unsigned m[100000];
  
  scanf("%d", &t);

  if(t <=0 || t > 100000)
    return -1;

  for(i = 0; i < t; i++)
    scanf("%d", m+i);

  for(i = 0; i < t; i++) {
    printf("%d\n", fctrl_tz(m[i]));
  }

  return 0;
}
