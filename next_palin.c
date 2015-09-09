/*
 * author: xuhd
 * problem link: http://www.spoj.com/problems/PALIN/
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

char* next_palin(char* pn)
{
  char *p = NULL, *tmp_p = NULL;
  char *q = NULL, *tmp_q = NULL;
  char *p_mid = NULL;
  int len = strlen(pn);
  int mid = len/2;
  int carry_flag = 0;

  *(pn-1) = '0';
  p = pn + mid - 1;
  q = pn + (len%2?mid+1:mid);
  p_mid = len%2?p+1:NULL;

  tmp_p = p;
  tmp_q = q;

  while( *q && *q == *p ) { p--; q++;}

  if( *q == '\0' ) { // input str is palin
    p = tmp_p;
    q = tmp_q;
    if( p < pn) {p = pn; q = pn; p_mid = pn;}
    if(p_mid && '9' != *p_mid) *p_mid += 1;
    else{
      while(*p == '9' && p >= pn){
        *p-- = '0';
        *q++ = '0';
      }
  
      if(p >= pn) {
        *p += 1;
        *q = *p;
      } else { //carry happened
        *p = '1';
        *--q = '1';
        carry_flag = 1;
      }
      if(p_mid&&*(p_mid+1))*p_mid = '0';
    }
  } else if( *q > *p ) {
    p = tmp_p;
    q = tmp_q;
    if(p+1 == q-1) p++; //if digit count is odd,point to middle
    while( '9' == *p )*p-- = '0';
    *p += 1;
    p = tmp_p;
    while( p >= pn ) *q++ = *p--;
  } else if( *q < *p ) {
    while( *q ) *q++ = *p--;
  }

  return carry_flag ? pn-1 : pn;
}

int main(void)
{
  int i, k;
  int t;
  char* a[100];

  scanf("%d", &t);

  if(t <=0 || t > 100)
    return -1;

  for(i = 0; i < t; i++) {
    a[i] = malloc(1000002);
    assert(a[i] != NULL);
  }
  
  for(i = 0; i < t; i++)
    scanf("%s", a[i] + 1); //reserve one for possible carry
  
  for(i = 0; i < t; i++) {
    printf("%s\n", next_palin(a[i]+1));
  }

  for(i = 0; i < t; i++)
    free(a[i]);

  return 0;
}

