/*
 * author: xuhd
 * problem link: http://www.spoj.com/problems/ARITH/
 */

#include <stdio.h>

int main()
{
  int t, i, k, a;
  char exp[1024];
  char op;
  char *p, *pa, *pb;
  int la, lb, len;
  char dash[2048], queue_a[2048], queue_b[2048], result[2048];
  int rear_d, rear_a, rear_b, top;
  int carry, borrow;
  int check_offset;

  scanf("%d", &t);

  if( t<=0 || t>1000 )
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
      while(la){
	a = (*(pa+la---1)-'0') - borrow;
	borrow = a<0?1:0;
	result[++top] = '0'+a+10*borrow;
      }
      i = 0;
      while('0'==result[top+i]){result[top+i--]=' ';} //replace leading zero with spaces
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
      //len = la>lb+1?la:lb+1;
      len = la+lb-1;
      
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

      //======== for first dash line ============
      rear_d = 0;
      for(i=0; i<=len; i++) {
	//putchar('-');
	dash[rear_d++] = '-';
      }
      //putchar('\n');
      dash[rear_d++] = '\n';
      dash[rear_d] = '\0';

      //====== for middle result, or the final result if 1 == la =====
      for(i = 0; i < la; i++) {
	;
      }

      if(la > 1) {
	//======== for the second dash line
        //======== for the final result  ==========
        for(i = 0; i < len; i++)
	  result[i] = '?';
	result[++i] = '\0';

	printf("%s", queue_a);
	printf("%s", queue_b);
	printf("%s", dash);

	printf("%s\n", result);
      }
    }
  }

  return 0;
}
