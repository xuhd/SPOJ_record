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

#define BFSZ (10240)

int main(int argc, char *argv[])
{
    int k;
    int m;
    int t;
    char *pkey = NULL;
    int *pf = NULL;
    int i = 0, j, n;
    int c = 0;
    char chr;
    char s[16];
    int ret = 0;
    char buf[BFSZ];
    int found_flag;
    int not_finish = 1;
    int needle_offset = 0;
    int haystack_offset = 0;

  while(not_finish){
  LBL:
    if(pkey)free(pkey);
    if(pf)free(pf);
    n = 0;
    if(0==ret){
      while(1==read(0, &chr, 1) && '\n'!=chr) 
	s[n++] = chr;
      s[n] = '\0';
    }
    else{
      j = c-ret;
      while(j < c && buf[j] != '\n'){
	s[n++] = buf[j++];
	ret--;
	i++;
      }
      if(j==c){
	while(1==read(0, &chr, 1) && '\n'!=chr) 
	  s[n++] = chr;
	s[n] = '\0';
      }else{
	s[n] = '\0';
	ret--;i++; //eat '\n'
      }
    }

    t = atoi(s);
    if(0==t)break;
    pkey = (char*)malloc(t+1);
    if(0==ret){
      read(0, pkey, t+1);
      pkey[t] = '\0'; 
    }else{
      j = c - ret;
      n = 0;
      while(ret > 0 && buf[j] != '\n'){
	pkey[n++] = buf[j++];
	ret--;i++;  //eat
      }
      if(ret>0) {
	pkey[n] = '\0';
	ret--;i++; //eat '\n'
      }else{
	i = 0; //reset i;
	read(0, pkey+n, t+1-n);
	pkey[t] = '\0';
      }
    }
        
    m = t;
        
        
        //    kmp_matcher(pkey, t);
    {
      char* q = pkey;
    
      pf = (int*)malloc(m * sizeof(int));
      failure(pkey, pf, m);
                
      k = 0;
      found_flag = 0;
      if(0 == ret){
	i=0;
      }
      haystack_offset = 0;
      while( ret > 0 || (c = ret = read(0, buf, BFSZ)) > 0) {
	if(ret<=0) {not_finish=0; break;}

	while( ret ){
	  if('\n' == buf[i%c]) {
	    ret--;i++;
	    haystack_offset = 0;
	    if(found_flag)putchar('\n');
	    goto LBL;
	  }
	  haystack_offset++;
	  ret--;
	  while( k > 0 && q[k] != buf[i%c] )
	    k = pf[k-1];
	  if(q[k] == buf[i%c])
	    k++;
	  if(k == m) {
	    found_flag=1;
	    printf("%d\n", haystack_offset-m);
	  }
	  i++;
	}
	i = 0;
      }
      free(pf);
      pf = NULL;
    }//end of kmp matcher
        
    //printf("\n");
    free(pkey);
    pkey=NULL;
  }
    
  return 0;
}
