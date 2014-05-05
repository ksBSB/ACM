#include <stdio.h>
#include <string.h>
const int N = 10005;

struct State {
    int w;
    int s;
}tmp[N];
int n, dp[N], vis[N];

int find(int cur) {
    if (dp[cur])    return dp[cur];
    int a;
    vis[cur] = cur;
    State& now = tmp[cur];
    for (int i = 0; i < n; i++) {
  if (tmp[i].w < now.w && tmp[i].s > now.s) {
      a = find(i);
      if (dp[cur] <= a) {
    dp[cur] = a;
    vis[cur] = i;
      }
  }
    }
    return ++dp[cur];
}

void solve() {
    int Max = 0, id = 0, ans[N], cnt = 0;
    for (int i = 0; i < n; i++) {
  if (!dp[i]) find(i);
  if (Max < dp[i]) {
      Max = dp[i];
      id = i;
  }
    }

    printf("%d\n", Max);
    while (id != vis[id]) {
  ans[cnt++] = id + 1;
  id = vis[id];
    }
    ans[cnt++] = id + 1;

    for (int i = cnt - 1; i >= 0; i--)
  printf("%d\n", ans[i]);

}

int main() {
    // Init;
    n = 0;
    memset(tmp, 0, sizeof(tmp));
    memset(vis, 0, sizeof(vis));
    memset(dp, 0, sizeof(dp));

    // Read;
    while(scanf("%d%d", &tmp[n].w, &tmp[n].s) == 2)
  n++;

    solve();

    return 0;
}
