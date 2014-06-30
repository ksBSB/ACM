#include <stdio.h>
#include <string.h>
const int N = 105;
const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int max(int a, int b) { return a > b ? a : b; }
int R, C, g[N][N], rec[N][N];
char name[N];

int find(int x, int y) {
    if (rec[x][y])  return rec[x][y] + 1;
    rec[x][y] = 1;
    int p, q;
    for (int i = 0; i < 4; i++) {
  p = x + dir[i][0], q = y + dir[i][1];
  if (p < 0 || p >= R)    continue;
  if (q < 0 || q >= C)    continue;
  if (g[x][y] > g[p][q])
      rec[x][y] = max(find(p, q), rec[x][y]);
    }
    return rec[x][y] + 1;
}

void solve() {
    int Max = 0;
    memset(rec, 0, sizeof(rec));
    for (int i = 0; i < R; i++) {
  for (int j = 0; j < C; j++) {
      if (!rec[i][j]) {
    int p, q;
    rec[i][j] = 1;
    for (int k = 0; k < 4; k++) {
        p = i + dir[k][0], q = j + dir[k][1];
        if (p < 0 || p >= R)    continue;
        if (q < 0 || q >= C)    continue;
        if (g[i][j] > g[p][q])
      rec[i][j] = max(find(p, q), rec[i][j]);
    }
      }
      if (Max < rec[i][j])  Max = rec[i][j];
  }
    }
    printf("%s: %d\n", name, Max);
}

int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
  scanf("%s%d%d", name, &R, &C);
  for (int i = 0; i < R; i++)
      for (int j = 0; j < C; j++)
    scanf("%d", &g[i][j]);
  solve();
    }
    return 0;
}
