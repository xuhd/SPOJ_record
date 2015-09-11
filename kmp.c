/*
 * author: xuhd
 * problem link: http://www.spoj.com/problems/NHAY/
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int failure(char* p_key, int* p_arr, int arr_size)
{
  int m = 0, i = 0, k = 0;
  
  if(NULL == p_key || NULL == p_arr)
    return 0;

  while(p_key[i++])m++; // length of key

  if(m > arr_size)
    return 0;

  p_arr[0] = 0;
  for(i = 1; i < m; i++) {
    while(k > 0 && p_key[k] != p_key[i])
      k = p_arr[k-1];
    if(p_key[k] == p_key[i])
      k++;
    p_arr[i] = k;
  }

  return m;
}

static void kmp_matcher(char* p_key, int m)
{
  int i = 0, k = 0;
  char* q = p_key;
  int* pf;
  char c;
  int ret;

  pf = (int*)malloc(m * sizeof(int));
  failure(p_key, pf, m);

  for(i = 0; 1==read(0, &c, 1) && '\n'!=c; i++){
    while( k > 0 && q[k] != c )
      k = pf[k-1];
    if(q[k] == c)
      k++;
    if(k == m)
      printf("%d\n", i-m+1);
  }

  free(pf);
  return;
}


int main(int argc, char *argv[])
{
  int t;
  char *pkey;
  int i;
  char c;
  char s[16];

  while(1){
    i = 0;
    while(1==read(0, &c, 1) && '\n'!=c)
      s[i++] = c;
    s[i] = '\0';
    t = atoi(s);
    if(0==t)break;
    pkey = (char*)malloc(t+1);
    i = 0;
    while(1==read(0, &c, 1) && '\n'!=c)
      pkey[i++] = c;
    pkey[i] = '\0';

    kmp_matcher(pkey, t);

    printf("\n");
    free(pkey);
  }

  return 0;
}
