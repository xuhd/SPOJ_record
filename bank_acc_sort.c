#include <stdio.h>

typedef unsigned long long ull;

#define MAX_ACC_CNT (100*1000 + 1)

static char acc_tbl[MAX_ACC_CNT][33];

int rdline(char* buf, int size)
{
  int i;
  char ch;

  scanf(" %[^\n]", buf);
  return 0;

  fsync(0);
  i = 0;
  while( i < size && 1 == read(0, &ch, 1) ) {
    buf[i] = ch;
    if('\n' == ch) break;
    i++;
  }
  buf[i] = '\0';

  return i;
}

int cmp(void* a, void* b)
{
  char *p, *q;

  p = (char*)a;
  q = (char*)b;
  return strcmp(p,q);
}

int main()
{
  int t, i, n, j, dup, k;
  ull *p, *q, m;
  char num[7];

  if(sizeof(m) != 8)
    return -1;

  scanf("%d", &t);
  //rdline(num, sizeof(num));
  //t = atoi(num);
  for(i = 0; i < t; i++) {
    scanf("%d", &n);
    //rdline(num, sizeof(num));
    //n = atoi(num);
    for(j = 0; j < n; j++)
      rdline(acc_tbl[j], sizeof(acc_tbl[0]));

    qsort(acc_tbl, n, sizeof(acc_tbl[0]), cmp);

    dup = 1;
    for(j = 0; j < n-1; j++) {
      if( 0 == strcmp(acc_tbl[j], acc_tbl[j+1]) ) {
	dup++;
      } else {
	printf("%s%d\n", acc_tbl[j], dup);
	dup = 1;
      }
    }
    printf("%s%d\n", acc_tbl[j], dup);

    printf("\n");
  }

  return 0;
}
