#include <stdio.h>

char graph[2002][2002] = {0};
char masks[] = {0, 3, 9, 12, 6, 15};
short q[4000000][2];
int qpos = 0;
int qlast = 0;

void bfs(int i, int j){
  q[qpos][0] = i;
  q[qpos][1] = j;
  qlast = (qlast+1)%4000000;

  while(qlast != qpos){
    i = q[qpos][0];
    j = q[qpos++][1];
    qpos %= 4000000;

    if((graph[i][j] & 1) && (graph[i][j-1] & 4)){
      q[qlast][0] = i;
      q[qlast++][1] = j-1;
      qlast %= 4000000;
    }
    if((graph[i][j] & 4) && (graph[i][j+1] & 1)){
      q[qlast][0] = i;
      q[qlast++][1] = j+1;
      qlast %= 4000000;
    }
    if((graph[i][j] & 2) && (graph[i+1][j] & 8)){
      q[qlast][0] = i+1;
      q[qlast++][1] = j;
      qlast %= 4000000;
    }
    if((graph[i][j] & 8) && (graph[i-1][j] & 2)){
      q[qlast][0] = i-1;
      q[qlast++][1] = j;
      qlast %= 4000000;
    }
    graph[i][j] = 0;
  }
}

int main(){
  int n, m;
  int i, j;
  int cntr = 0;
  char temp[2004];
  scanf("%d %d", &n, &m);
  int c;

  for(i = 1; i <= n; ++i){
    while ((c = getchar()) != EOF && c != '\n');
    fgets(temp, m+1, stdin);

    for(j = 1; j <= m; ++j){
      graph[i][j] = masks[temp[j-1] - 'A'];
    }
  }

  for(i = 1; i <= n; ++i)
    for(j = 1; j <= m; ++j)
      if(graph[i][j] != 0){
        bfs(i, j);
        ++cntr;
      }

  printf("%d\n", cntr);
  return 0;
}
