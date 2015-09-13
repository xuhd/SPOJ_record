/*
 * author: xuhd
 * problem link: http://www.spoj.com/problems/PT07H/
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_DEPTH (8192)

typedef enum{
  TAG_START,
  TAG_END,
  TAG_ERROR
}tag_type_t;

typedef struct _node_t{
  char* p_name; //point to tag name
  int len; //tag name len
  int num; 
  int level;
  struct _node_t* l;
  struct _node_t* r;
} node_t, *tree_t;

static char sg_buf[100*1024]; //input file max 100KB
static int sg_cur;
static int sg_match_cnt;

tag_type_t get_next_tag(char** pp, int* plen)
{
  tag_type_t t;
  int i = sg_cur;
  char* p = sg_buf + i;

  while( *p && isspace(*p) ){p++;i++;} //skip white spaces
  
  if('\0' == *p) return TAG_ERROR;

  if( '<' == *p && '/' == *(p+1) ) {
    t = TAG_END;
    i+=2;
    p+=2;
  } else {
    t = TAG_START;
    i+=1;
    p+=1;
  }

  *pp = p;
  *plen = 0;
  while( '>' != *p ){(*plen)++; p++;}
  *p = '\0';  //tricky! we do not have to visit the buffer again, so it is safe to replace '>' with '\0'
  i += *plen;
  i += 1; //skip '>'
  sg_cur = i;

  return t;
}

#define MAX_MATCH_CNT (8192)
#define MAX_MATCH_LEN (8192)
static int sg_match_path[MAX_MATCH_CNT][MAX_MATCH_LEN];

void match_tree(tree_t tree, tree_t ptn)
{
  static int m;
  if(NULL==tree || NULL==ptn)return;
  if(0 == strcmp(tree->p_name, ptn->p_name)) {
    sg_match_path[sg_match_cnt][m++] = tree->num;
    if( NULL == ptn->l && NULL == ptn->r ){
      m = 0;
      sg_match_cnt++;
      //printf("%d\n", tree->num);
    }else if(tree->l && ptn->l)
      match_tree(tree->l, ptn->l);
    else if(tree->r && ptn->r)
      match_tree(tree->r, ptn->r);
  }

  if(tree->l)match_tree(tree->l, ptn);
  if(tree->r)match_tree(tree->r, ptn);
}

node_t* make_tree_node(char* pname, int len, int level)
{
  static int node_idx;
  node_t* p_node = malloc(sizeof(node_t));

  p_node->p_name = pname;
  p_node->len = len;
  p_node->level = level;
  p_node->l = NULL;
  p_node->r = NULL;
  p_node->num = ++node_idx;

  return p_node;
}

void free_tree(node_t* p_tree)
{
  if(NULL == p_tree) return;
  if(p_tree->l) free_tree(p_tree->l);
  if(p_tree->r) free_tree(p_tree->r);
  free(p_tree);
}

int main()
{
  int ret;
  int i, j;
  tree_t tree, ptn_tree;
  char *pname;
  int len;
  int top;
  node_t* node_stack[MAX_DEPTH];
  node_t* p;
  tree_t sub_tree[MAX_DEPTH];
  tag_type_t t;

  ret = read(0, sg_buf, sizeof(sg_buf));
  sg_buf[ret] = '\0';
  sg_cur = 0;

  for(i = 0; i < 2; i++) {
    top = -1;
    for(j = 0; j < MAX_DEPTH; j++){
      node_stack[j] = NULL;
      sub_tree[j] = NULL;
    }

    get_next_tag(&pname, &len);
    node_stack[++top] = make_tree_node(pname, len, top);
    while(top >= 0) {
      t = get_next_tag(&pname, &len);
      if(TAG_START == t)
	node_stack[++top] = make_tree_node(pname, len, top);
      else if(TAG_END == t) {
	node_t** pp;
	node_t *pn, *tmp;

	p = node_stack[top--];
	pp = &sub_tree[p->level];
	if(NULL == *pp) *pp = p;
	else {
	  pn = *pp;
	  while(pn){tmp = pn; pn = pn->r;};
	  pn = tmp;
	  pn->r = p;
	}
	pp = &sub_tree[p->level + 1];
	if(*pp) {
	  p->l = *pp;
	  *pp = NULL;
	}
      }
    }

    if(0 == i) tree = node_stack[0];
    else ptn_tree = node_stack[0];
  }

  match_tree(tree, ptn_tree);

  printf("%d\n", sg_match_cnt);
  for(i = 0; i < sg_match_cnt; i++)
    printf("%d\n", sg_match_path[i][0]);

  free_tree(tree);
  free_tree(ptn_tree);
  return 0;
}
