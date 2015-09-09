/*
 * author: xuhd
 * problem link: http://www.spoj.com/problems/HASHIT/
 */

#include <stdio.h>
#include <string.h>

#define NSLOT (101)
#define KEYLEN (32)
#define MAX_TRY (20)

#define OP_ADD "ADD"
#define OP_DEL "DEL"

static char tbl[NSLOT][KEYLEN];

int hash(char* key)
{
  int i, val = 0, len = strlen(key);

  for(i = 0; i < len; i++)
    val += key[i]*(1+i);
  val *= 19;
  
  return val % NSLOT;
}

int get_free_slot(char* key)
{
  int j, slot;

  for( j = 0; j < MAX_TRY; j++ ) {
    slot = (hash(key) + j*j + 23*j) % NSLOT;
    if( '\0' == tbl[slot][0] ) //free slot
      return slot;
  }

  return -1;
}

int search_key(char* key)
{
  int j, slot;

  for( j = 0; j < MAX_TRY; j++ ) {
    slot = (hash(key) + j*j + 23*j) % NSLOT;
    if( strcmp(key, tbl[slot]) )
      continue;
    else
      return slot;
  }

  return -1;
}


void add(char* key)
{
  int slot, k = 0;

  if( -1 == search_key(key)) {
    slot = get_free_slot(key);
    if( slot >= 0 )
      while(tbl[slot][k++] = *key++);
  }
}

void del(char* key)
{
  int slot = search_key(key);

  if( slot >= 0 )
    tbl[slot][0] = '\0';
}

int main()
{
  int t, n, i, k, cnt;

  char cmd[32], *p_op, *p_key;

  scanf("%d", &t);

  if(t <=0 || t > 100)
    return -1;

  p_op = &cmd[0];
  for(i = 0; i < t; i++) {
    for(k = 0; k < NSLOT; k++)
      tbl[k][0] = '\0';

    scanf("%d", &n);

    for(k = 0; k < n; k++) {
      char *p;
      scanf("%s", cmd);
      p = strchr(cmd, ':');
      *p = '\0';
      p_key = p+1;
      if( 0 == strcmp(p_op, OP_ADD) ) {
        add(p_key);
      }else if( 0 == strcmp(p_op, OP_DEL) ) {
        del(p_key);
      }else
        ;
    }
    cnt = 0;
    for( k = 0; k < NSLOT; k++)
      if(tbl[k][0] != '\0') cnt++;
    printf("%d\n", cnt);
    for( k = 0; k < NSLOT; k++)
      if(tbl[k][0] != '\0') printf("%d:%s\n", k, tbl[k]);
  }

  return 0;
}
