/*
 * Author: xuhd
 * problem link: http://www.spoj.com/problems/MKMOOM/
 */
#include <stdio.h>
#include <string.h>

#define MAX_ARGS (100)
#define MAX_MACROS (256)

typedef struct {
  char p_mcr[2][128];
}macro_entry_t;


typedef struct {
  char name[33];
  char args[MAX_ARGS][33];
  int nargs;
}expan_info_t;


static macro_entry_t macro_table[MAX_MACROS];
static int entry_cnt;

char* get_macro_def(char* pm)
{
  char *p;
  int i;

  for(i = 0; p = macro_table[i].p_mcr[0]; i++)
    if( 0 == strcmp(pm, p) ) return macro_table[i].p_mcr[1];

  return NULL;
}

void install_macro(char* p_macro)
{
  char *p;
  int n;

  //printf("macro name: %s\n", p_macro);
  n = 0;
  while( p = strtok(NULL, ",") )
    strcpy(macro_table[entry_cnt].p_mcr[n++], p);

  entry_cnt++;
}

int get_rep(char* macr_def, expan_info_t* p_info, char* buf, int size)
{
  int i, j, k, ai;
  char ch;


  i = 0;
  k = 0;
  while( ch = macr_def[i] ) {
    switch( ch ) {
    case '<': // start of macro def string
      break;

    case '>': // end of macro def string
      break;

    case '$':
      ai = -1;
      if(isdigit(ch = macr_def[++i]))
	ai = atoi(macr_def+i);
      if(0 == ai) {
	j = 0;
	while(buf[k++] = p_info->name[j++]);
	k--; //unget '\0'
      }else if(ai > 0) {
	j = 0;
	while(buf[k++] = p_info->args[ai-1][j++]);
	k--; //unget '\0'
      }
      if(ai < 0);
      else if(ai < 10);
      else if(ai < 100)i+=1;
      else ; //no that many arguments
      break;

    default:
      buf[k++] = ch;
      break;
    }
    i++;
  }

  buf[k] = '\0';
  return k;
}

//char* expand_macro(char* p_macro)
char* macro_proc(char* p_macro)
{
  char *p, *pm, *pd;
  int i, k;
  expan_info_t stack[MAX_MACROS];
  int top;
  char ch;
  int n;
  char s[33];
  char rep[81];
  int ret;

  p = p_macro;
  memset(stack, 0, sizeof(stack));
  top = -1;
  i = 0;
  k = 0;
  while(ch = p[i]) {
    switch( ch ) {
    case '[':
      if(top>=0) stack[top].nargs = n;
      top++;
      i++;
      n = 0;
      ret = 0;
      break;
    case ']':
      s[k] = '\0';
      k = 0;
      if(0==n) {
	strcpy(stack[top].name, s);
	stack[top].nargs = 0;
	n++;
      } else {
	strcpy(stack[top].args[n-1], s);
	stack[top].nargs = n;
	n++;
      }

      pm = stack[top].name;
      if(0 == strcmp(pm, "def")) { //install macro
	strcpy(macro_table[entry_cnt].p_mcr[0], stack[top].args[0]);
	strcpy(macro_table[entry_cnt].p_mcr[1], stack[top].args[1]);
	entry_cnt++;
      } else {
	pd = get_macro_def(pm);
	if(pd)
	  ret = get_rep(pd, &stack[top], rep, sizeof(rep));
	//printf("%s", rep);
      }
      //n = stack[top].nargs;
      top--;
      if(top>=0) {
	n = stack[top].nargs;
	if(0 == n)
	  strcpy(stack[top].name, rep);
	else if(n > 0)
	  strcpy(stack[top].args[n-1], rep);
	n++;
	if(',' == p[i+1])
	  i+=2; //eat ']' and next ','
      } else if(ret > 0) {
	memset(stack, 0, sizeof(stack));
	printf("%s", rep);
	i++;
      } else
	i++;
      break;
    case ',':
      s[k] = '\0';
      k = 0;
      if(0==n) {
	strcpy(stack[top].name, s);
	stack[top].nargs = 0;
	n++;
      } else {
	strcpy(stack[top].args[n-1], s);
	stack[top].nargs = n;
	n++;
      }
      i++;
      break;
    case '\n':
      putchar(ch);
      i++;
      break;
    default:
      if(top>=0)
	s[k++] = ch;
      else
	putchar(ch);
      i++;
      break;
    }

      
  }
}

/*
int macro_proc(char* in)
{
  int i;
  char ch;
  char *p_macro;
  int n;

  i = 0;
  while( ch = in[i] ) {
    switch(ch) {
    case '[':
      n = 1;
      while( ']' != in[i+n] ) {
	if( '<' == in[i+n-1] && '>' == in[i+n+1] ) {
	  n++;
	  continue;
	}
        n++;
      }
      in[i+n] = '\0';
      p_macro = in+1;
      p_macro = strtok(&in[i+1], ",");
      if(0 == strcmp(p_macro, "def")) {
	install_macro(p_macro);
      } else {
	expand_macro(p_macro);
      }

      i += n+1;
      break;

    case '\n':
      putchar('\n');
      i++;
      break;

    default:
      putchar(ch);
      i++;
      break;
    }
  }
}
*/

int rdline(char* buf, int size)
{
  int i;
  char ch;

  i = 0;
  while( i < size && 1 == read(0, &ch, 1) ) {
    buf[i++] = ch;
    if('\n' == ch) break;
  }
  buf[i] = '\0';

  return i;
}

int main()
{
  int t, i, cnt, n;
  char line[82];
  char ln[82];
  char input[811];

  rdline(ln, sizeof(ln));
  t = atoi(ln);
  cnt = 0;
  while( t != 0 ) {
    memset(macro_table, 0, sizeof(macro_table));
    entry_cnt = 0;
    printf("Case %d\n", ++cnt);
    for(i = 0; i < 79; i++) putchar('-');
    putchar('\n');

    n = 0;
    for(i = 0; i < t; i++) {
      //scanf("%s", line);
      rdline(line, sizeof(line));
      sprintf(input, "%s%s", input, line);
    }

    macro_proc(input);

    for(i = 0; i < 79; i++) putchar('-');
    putchar('\n');
    putchar('\n');

    rdline(ln, sizeof(ln));
    t = atoi(ln);
    input[0] = '\0';
  }
  
  return 0;
}
