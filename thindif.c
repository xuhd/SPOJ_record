/*
 * author: xuhd
 * problem link: http://www.spoj.com/problems/THINDIF/
 */


#include <stdio.h>

int main()
{
  int i, t;
  long double m, a;

  scanf("%d", &t);
  for(i = 0; i < t; i++) {
    scanf("%Lf %Lf", &m, &a);
    printf("%.6Lf\n", (m*m+a)/(2.0*m));
  }

  return 0;
}
