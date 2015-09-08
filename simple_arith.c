#include <stdio.h>

int main()
{
  int t, i, a;
  char exp[1024];
  char op;
  char *p, *pa, *pb;
  int la, lb, len;
  char line[2048];
  int top, carry, borrow;

  scanf("%d", &t);

  if( t<=0 || t>1000 )
    return -1;

  for(i = 0; i < t; i++) {
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
	borrow = a<1?1:0;
   	line[++top] = '0'+a+10*borrow;
      }
      while(la){line[++top] = *(pa+la---1)-borrow; borrow=0;}
      while(top>=0)putchar(line[top--]);
      putchar('\n');

      break;

    case '+':
      len = la>lb+1?la:lb+1;
      for(i=0; i<len-la; i++)
	putchar(' ');
      printf("%s\n", pa);
      for(i=0; i<len-lb-1; i++)
	putchar(' ');
      putchar('+');
      printf("%s\n", pb);
      for(i=0; i<len; i++)
	putchar('-');
      putchar('\n');
      top = -1;
      carry = 0;
      while(la&&lb) {
	a = (*(pa+la---1)-'0') + (*(pb+lb---1)-'0') + carry;
	carry = a>9?1:0;
   	line[++top] = '0'+a-10*carry;
      }
      while(la){
	a = *(pa+la---1) - '0' + carry;
	carry = a>9?1:0;
	line[++top] = '0'+a-10*carry;
      }
      while(lb){
	a = *(pa+lb---1) - '0' + carry;
	carry = a>9?1:0;
	line[++top] = '0'+a-10*carry;
      }
      if(carry)line[++top] = '1';
      while(top<len-1)line[++top] = ' ';
      while(top>=0)putchar(line[top--]);
      putchar('\n');
      break;

    case '*':
      break;
    }
  }

  return 0;
}
