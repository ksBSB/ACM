#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 50;

int n, w, dp[N], vis[N], seq[N][N];

void Init() {
    memset(dp, 0, sizeof(dp));
    memset(vis, 0, sizeof(vis));
    memset(seq, 0, sizeof(seq));
}

void read() {
    for (int i = 0; i < n; i++) {
  for (int j = 0; j < w; j++)
      scanf("%d", &seq[i][j]);
  sort(seq[i], seq[i] + w);
    }
}

bool judge(int a, int b) {
    for (int i = 0; i < w; i++)
  if(seq[a][i] <= seq[b][i])  return false;
    return true;
}

int find(int d) {
    if (dp[d])  return dp[d];

    for (int i = 0; i < n; i++) {
  if (judge(i, d)) {
      int a = find(i);
      if (a > dp[d]) {
    dp[d] = a;
    vis[d] = i;
      }
  }
    }
    return ++ dp[d];
}

void solve() {
    int Max = 0, id, a;
    for (int i = 0; i < n; i++) {
  a = find(i);
  if (a > Max) {
      Max = a;
      id = i;
  }
    }
    printf("%d\n", Max);
    for (int i = 1; i < Max; i++) {
  printf("%d ", id + 1);
  id = vis[id];
    }
    printf("%d\n", id + 1);
}


int main() {
    while (scanf("%d%d", &n, &w) == 2) {
  Init();
  read();
  solve();
    }
    return 0;
}
