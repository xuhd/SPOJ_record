#include <stdio.h>
#include <string.h>

int main()
{
  int i, t, j, k, n, d;
  int m[100][100];

  scanf("%d", &t);
  for(i = 0; i < t; i++) {
    memset(m, 0, sizeof(m));
    scanf("%d %d", &k, &d);
    for(j = 0; j < k; j++) {
      scanf("%d", &m[0][j]);
    }

    for(n = 1; n < k; n++) {
      for(j = 0; j < k-n; j++)
	m[n][j] = m[n-1][j+1] - m[n-1][j];
    }
    
    for(n = k-1; n >= 0; n--) {
      for(j = 0; j < d; j++) {
	m[n][k-n+j] = m[n+1][k-n+j-1] + m[n][k-n+j-1];
      }
    }

    for(j = 0; j < d-1; j++)
      printf("%d ", m[0][k+j]);
    printf("%d\n", m[0][k+j]);
  }

  return 0;
}
