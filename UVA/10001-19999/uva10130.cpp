#include <stdio.h>
#include <string.h>
const int N = 1005;
const int M = 100005;

int n, m, Sum, Max, p[N], w[N], dp[M];

void Init() {
    Sum = Max = 0;
    memset(p, 0, sizeof(p));
    memset(w, 0, sizeof(w));
    memset(dp, 0, sizeof(dp));
}

void solve() {
    for (int i = 0; i < n; i++) {
  for (int j = Sum; j >= w[i]; j--) {
      if (dp[j] < dp[j - w[i]] + p[i])
    dp[j] = dp[j - w[i]] + p[i];
  }
    }
}

int find(int cur) {
    int t = 0;
    for (int i = 0; i <= cur; i++)
  if (t < dp[i])  t = dp[i];
    return t;
}

int main() {
    int cas, t;
    scanf("%d", &cas);
    while (cas--) {
  Init();

  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
      scanf("%d%d", &p[i], &w[i]);
      Sum += w[i];
  }

  solve();

  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
      scanf("%d", &t);
      Max += find(t);
  }

  printf("%d\n", Max);
    }
    return 0;
}
