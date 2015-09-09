/*
 * author: xuhd
 * problem link: http://www.spoj.com/problems/ARITH/
 */

#include <stdio.h>

int main()
{
  int t, i, j, k, a, c, m;
  char exp[1024];
  char op;
  char *p, *pa, *pb;
  int la, lb, len, prodlen;
  char spaces[512];
  char dash[2048], queue_a[2048], queue_b[2048], result[2048];
  char mid_result[512][512];
  int rear_d, rear_a, rear_b, top;
  int carry, borrow;
  int check_offset;

  scanf("%d", &t);

  if( t<=0 || t>10000 )
    return -1;

  for(k = 0; k < t; k++) {
    scanf("%s", exp);
    la = lb = 0;
    pa = p = exp;
    while(isdigit(*p)){la++;p++;}
    op = *p;
    *p++ = '\0';
    pb = p;
    while(*p++)lb++;

    switch(op){
    case '-':
      len = la>lb+1?la:lb+1;
      for(i=0; i<len-la; i++)
	putchar(' ');
      printf("%s\n", pa);
      for(i=0; i<len-lb-1; i++)
	putchar(' ');
      putchar('-');
      printf("%s\n", pb);
      for(i=0; i<len; i++)
	putchar('-');
      putchar('\n');
      top = -1;
      borrow = 0;
      while(la&&lb) {
	a = (*(pa+la---1)-'0') - borrow - (*(pb+lb---1)-'0');
	borrow = a<0?1:0;
   	result[++top] = '0'+a+10*borrow;
      }
      
      if(0==la&&0==lb)result[++top] = ' ';
      
      while(la){
	a = (*(pa+la---1)-'0') - borrow;
	borrow = a<0?1:0;
	result[++top] = '0'+a+10*borrow;
      }
      
      i = 0;
      while('0'==result[top+i]||' '==result[top+i]) {
	result[top+i--]=' '; //replace leading zero with spaces
      }
      while(top>=0)putchar(result[top--]);
      putchar('\n');

      break;

    case '+':
      len = la>lb+1?la:lb+1;
      if(lb<la)check_offset=1;
      else check_offset=0;
      //======== for first number =========
      rear_a = 0;
      queue_a[rear_a++] = ' '; //first entry is reserved for possibly one additional space' '
      for(i=0; i<len-la; i++) {
	//putchar(' ');
	queue_a[rear_a++] = ' ';
      }
      //printf("%s\n", pa);
      i = 0;
      while(*(pa+i)) queue_a[rear_a++] = *(pa+i++);
      queue_a[rear_a++] = '\n';
      queue_a[rear_a] = '\0'; //end of first number


      //======== for second number =========
      rear_b = 0;
      queue_b[rear_b++] = ' '; //first entry is reserved for possibly one additional space' '
      for(i=0; i<len-lb-1; i++) {
	//putchar(' ');
	queue_b[rear_b++] = ' ';
      }
      //putchar('+');
      queue_b[rear_b++] = '+';
      //printf("%s\n", pb);
      i = 0;
      while(*(pb+i)) queue_b[rear_b++] = *(pb+i++);
      queue_b[rear_b++] = '\n';
      queue_b[rear_b] = '\0'; //end of second number

      //======== for dash line ============
      rear_d = 0;
      for(i=0; i<=len; i++) {
	//putchar('-');
	dash[rear_d++] = '-';
      }
      //putchar('\n');
      dash[rear_d++] = '\n';
      dash[rear_d] = '\0';

      //======== for the result =========
      top = -1;
      carry = 0;
      while(la&&lb) {
	a = (*(pa+la---1)-'0') + (*(pb+lb---1)-'0') + carry;
	carry = a>9?1:0;
   	result[++top] = '0'+a-10*carry;
      }
      while(la){
	a = *(pa+la---1) - '0' + carry;
	carry = a>9?1:0;
	result[++top] = '0'+a-10*carry;
      }
      while(lb){
	a = *(pb+lb---1) - '0' + carry;
	carry = a>9?1:0;
	result[++top] = '0'+a-10*carry;
      }
      if(carry)result[++top] = '1';
      while(top<len-1)result[++top] = ' ';

      if(check_offset && carry){
        printf("%s", queue_a);
        printf("%s", queue_b);
        printf("%s", dash);
      }else{
        printf("%s", queue_a+1);
        printf("%s", queue_b+1);
        printf("%s", dash+1);
      }
      while(top>=0)putchar(result[top--]);
      putchar('\n');
      break;

    case '*':
      len = la>lb+1?la:lb+1;
      
      //======== for first number =========
      rear_a = 0;
      for(i=0; i<len-la; i++) {
	//putchar(' ');
	queue_a[rear_a++] = ' ';
      }
      //printf("%s\n", pa);
      i = 0;
      while(*(pa+i)) queue_a[rear_a++] = *(pa+i++);
      queue_a[rear_a++] = '\n';
      queue_a[rear_a] = '\0'; //end of first number


      //======== for second number =========
      rear_b = 0;
      for(i=0; i<len-lb-1; i++) {
	//putchar(' ');
	queue_b[rear_b++] = ' ';
      }
      //putchar('+');
      queue_b[rear_b++] = '*';
      //printf("%s\n", pb);
      i = 0;
      while(*(pb+i)) queue_b[rear_b++] = *(pb+i++);
      queue_b[rear_b++] = '\n';
      queue_b[rear_b] = '\0'; //end of second number

      //======== for first dash line ============
      rear_d = 0;
      for(i=0; i< len; i++) {
	//putchar('-');
	dash[rear_d++] = '-';
      }
      //putchar('\n');
      dash[rear_d++] = '\n';
      dash[rear_d] = '\0';


      //====== for middle result, or the final result if 1 == la =====
      top = -1;

      m = *pb - '0';
      carry = 0;
      for(j = la-1; j >= 0; j--){
	c = *(pa+j) - '0';
	carry = (c*m+carry)/10;
      }
      if(carry>0)prodlen = la+lb; //determine how many digits in product
      else prodlen = la+lb-1;

      if( prodlen > len) {
	i = 0;
	len = prodlen;
	while(rear_d-1+i < len)spaces[i++] = ' ';
	spaces[++i] = '\0';
	printf("%s%s", spaces, queue_a);
	printf("%s%s", spaces, queue_b);
	printf("%s%s", spaces, dash);
      }else{
	printf("%s", queue_a);
	printf("%s", queue_b);
	printf("%s", dash);	
      }
      
      for(i = 0; i < lb; i++) {
	top = -1;
	for(j = 0; j < i; j++)
	  result[++top] = ' '; //to align the partial product with the right digit
	carry = 0;
	m = *(pb+lb-1-i) - '0';
	if(m>0){
	  for( j = la-1; j >= 0; j-- ) {
	    c = *(pa+j) - '0';
	    result[++top] = '0' + (c*m+carry)%10;
	    carry = (c*m+carry)/10;
	  }
	  if(carry>0)result[++top] = '0' + carry;
	}else{
	  result[++top] = '0';
	}

	while(top < len-1)result[++top] = ' ';

	j = 0;
	while(top>=0){
	  p = result + top--;
	  putchar(*p);
	  if(' ' == *p) *p = '\0'; //replace ' ' with '\0', prepare for adding
	  mid_result[i][j++] = *p;
	}
	putchar('\n');
      }

      //===== if the multiplier has more than one digit =====
      if(lb > 1) {
	//======== for the second dash line
	for(i = 0; i < len-prodlen; i++)
	  putchar(' ');
	for(i = 0; i < prodlen; i++)
	  putchar('-');
	putchar('\n');
        //======== for the final result  ==========
	top = -1;
	carry = 0;
        for(i = 0; i < len; i++){
	  a = 0;
	  for(j = 0; j <= i; j++){
	    m = mid_result[j][len-1-i];
	    if(m)m-='0';
	    a += m;
	  }
	  result[++top] = (a+carry)%10 + '0';
	  carry = (a+carry)/10;	  
	}
	i = 0;
	while('0'==result[top+i] || ' '==result[top+i]) {
	  result[top+i--]=' '; //replace leading zero with spaces
	}
	while(top>=0)putchar(result[top--]);
	putchar('\n');
      }
    }
    printf("\n");
  }

  return 0;
}
