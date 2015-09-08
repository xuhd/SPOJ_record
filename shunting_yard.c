#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int precedence[256];

static char* infix_to_rpn(char* infix)
{
  static char rpn[1024];
  char *p_in, *p_out;
  char opstack[512];
  int top = 0; //0 indicates stack empty

  p_in = infix;
  p_out = rpn;

  while( *p_in ) {
    if( isspace(*p_in) ) {p_in++; continue;}

    if( isalpha(*p_in) ) *p_out++ = *p_in++;
    else if ('(' == *p_in) {
      opstack[top++] = '(';
      p_in++;
    } else if(')' == *p_in) {
      while( top > 0 && opstack[top-1] != '(' )
	*p_out++ = opstack[--top];
      if( 0 == top )
        return "unmatched parenthesis";
      top--;
      p_in++;
    } else if( precedence[*p_in] != 0 ) {
      while( top > 0 && precedence[*p_in] <= precedence[opstack[top-1]] )
	*p_out++ = opstack[--top];

      opstack[top++] = *p_in++;
    } else
      return "unknown symbol";
  }

  while( top > 0 ) {
    if( '(' == opstack[top-1] || ')' == opstack[top-1] )
      return "unmatched parenthesis";
    else
      *p_out++ = opstack[--top];
  }

  *p_out = '\0';
  
  return rpn;
}


int main(void)
{
  int i, k;
  int t;
  char m[100][401];

  //install operator precedence
  memset(precedence, 0, sizeof(precedence));
  precedence['+'] = 10;
  precedence['-'] = 10;
  precedence['*'] = 20;
  precedence['/'] = 20;
  precedence['^'] = 30;
  
  scanf("%d", &t);

  if(t <=0 || t > 100)
    return -1;

  for(i = 0; i < t; i++)
    scanf("%s", m+i);

  for(i = 0; i < t; i++) {
    printf("%s\n", infix_to_rpn(m[i]));
  }
  
  return 0;
}
