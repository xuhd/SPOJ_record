/*
 * author: xuhd
 * problem link: http://www.spoj.com/problems/ADDREV/
 */

#include <stdio.h>

int rev(int d)
{
  char i = 0, r[16];

  while(0 == d%10)d/=10; //skip trailing zero
  do r[i++] = '0'+d%10; while(d/=10);
  r[i] = '\0';

  return atoi(r);
}

int main()
{
  int i, t, a, b;

  scanf("%d", &t);
  for(i = 0; i < t; i++) {
    scanf("%d %d", &a, &b);
    printf( "%d\n", rev(rev(a) + rev(b)) );
  }

  return 0;
}
