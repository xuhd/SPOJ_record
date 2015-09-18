#include <stdio.h>
#include <string.h>

int matrix[26][26];
int indegree[26], outdegree[26];
char visited[26];

void visit(int v) //depth first
{
  int i;

  visited[v] = 1;
  for(i = 0; i < 26; i++)
    if(matrix[v][i] && 0==visited[i]) visit(i);
}

int check_connect(int v)
{
  int i;

  for(i = 0; i< 26; i++)
    visited[i] = 0;

  visit(v);

  for(i = 0; i<26; i++)
    if(outdegree[i] && 0==visited[i]) return 0;

  return 1;
}

int main()
{
  int i, t, j, n, k, d, s, flag;
  char word[1001];
  char a, b;

  scanf("%d", &t);
  for(i = 0; i < t; i++) {
    scanf("%d", &n);

    memset(matrix, 0, sizeof(matrix));
    memset(outdegree, 0, sizeof(outdegree));
    memset(indegree, 0, sizeof(indegree));

    for(j = 0; j < n; j++) {
      scanf("%s", word);
      a = word[0];
      k = 1;
      while(word[k]) k++;
      k-=1;
      b = word[k];    // edge a--->b
      outdegree[a-'a']++;  //record out degree of vertex a
      indegree[b-'a']++;  //record in degree of vertex b
      matrix[a-'a'][b-'a']++;
    }

    d = 0;
    s = 0;
    for(j = 0; j < 26; j++) {
      if(outdegree[j] != indegree[j])
	if( outdegree[j] == indegree[j]+1 || outdegree[j]+1 == indegree[j]) {
	  if(outdegree[j] == indegree[j]+1)s=j; //record start vertex
	  d++;
	} else {
	  d = 3;
	  break;
	}
    }

    if(d > 2) {
      printf("The door cannot be opened.\n");
      continue;
    }

    flag = 0;
    for(j = s; j<26; j++) {
      if(outdegree[j] && check_connect(j)) {
	flag = 1;
	break;
      }
    }

    if(flag)
      printf("Ordering is possible.\n");
    else
      printf("The door cannot be opened.\n");

  }

  return 0;
}
