#include <stdio.h>
#include <string.h>
const int N = 10005;

int n, aid, sum, dp[N], vis[N], val[50];

void solve() {
    memset(dp, 0, sizeof(dp));
    memset(vis, 0, sizeof(vis));

    dp[0] = 1;
    for (int i = 0; i < n; i++) {
  for (int j = aid; j >= 0; j--) {
      if (dp[j] && dp[j + val[i]] == 0) {
    dp[j + val[i]] = 1;
    vis[j +val[i]] = val[i];
      }
  }
    }

    for (int i = aid; i >= 0; i--)
  if (dp[i])  {
      sum = i;
      break;
  }

    int cnt = 0, t = sum, ans[50];
    while (t >= 0 && vis[t]) {
  ans[cnt++] = vis[t];
//  printf("%d ", t);
  t -= vis[t];
    }

    for (int i = cnt - 1; i >= 0; i--)
  printf("%d ", ans[i]);
    printf("sum:%d\n", sum);
}

int main() {
    while (scanf("%d%d", &aid, &n) == 2) {
  memset(val, 0, sizeof(val));
  for (int i = 0; i < n; i++)
      scanf("%d", &val[i]);
  solve();
    }
    return 0;
}
