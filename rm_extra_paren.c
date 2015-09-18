#include <stdio.h>
#include <string.h>

int main()
{
  int i, t, j;
  char ch, expr[256];
  int top;
  int stack[256][3];
  char precd[128];
  char min_op, left_op, right_op;
  char flag[256];
  char peek;
  int left_paren;

  //install operator precedence
  memset(precd, 0, sizeof(precd));
  precd['+'] = 10;
  precd['-'] = 10;
  precd['*'] = 20;
  precd['/'] = 20;

  scanf("%d", &t);
  for(i = 0; i < t; i++) {
    scanf("%s", expr);
    j = 0;
    top = -1;
    min_op = 0;
    memset(stack, 0, sizeof(stack));
    memset(flag, 1, sizeof(flag));

    min_op = 0;
    left_op = 0;
    right_op = 0;
    while( ch = expr[j] ) {
      switch(ch) {
      case '(':
	++top;
	stack[top][0] = j; //position of left paren
	stack[top][2] = left_op;
	min_op = 0;
	break;

      case ')':
	left_paren = stack[top][0];
	min_op = stack[top][1];
	left_op = stack[top][2];
	top--;

	peek = expr[j+1];
	right_op = 0;
	if( precd[peek] )
	  right_op = peek;

	if( 0 == min_op || (0 == right_op && 0 == left_op)) {
	  flag[j] = 0;
	  flag[left_paren] = 0;

	  break;
	}

	if(right_op && precd[min_op] < precd[right_op]) 
	  break;
	if(left_op && precd[min_op] < precd[left_op])
	  break;
	if( '-' == left_op && precd['-'] == precd[min_op])
	  break;
	if( '/' == left_op )
	  break;

	flag[j] = 0;
	flag[left_paren] = 0;

	min_op = 0;
	break;

      case '+':
      case '-':
      case '*':
      case '/':
	left_op = ch;
	if( 0 == min_op ) min_op = ch;
	else if(precd[min_op] > precd[ch])
	  min_op = ch;

	if(top>=0)  stack[top][1] = min_op;

      default:
	break;
      }
      j++;
    }

    j = 0;
    while(ch = expr[j]) if(flag[j++])putchar(ch);
    putchar('\n');
  }

  return 0;
}

