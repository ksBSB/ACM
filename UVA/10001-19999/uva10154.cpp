#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 10005;
int min(int a, int b) { return a > b ? b : a; }

struct state {
    int w;
    int s;
}tmp[N];
int n, dp[N * 1000];

bool cmp (const state& a, const state& b) {
    return a.s > b.s;
}

void Init() {
    n = 0;
    memset(tmp, 0, sizeof(tmp));
    memset(dp, 0, sizeof(dp));
    while (scanf("%d%d", &tmp[n].w, &tmp[n].s) == 2)
      n++;
    sort(tmp, tmp + n, cmp);
}

int solve() {
    int Max = tmp[0].s, t;
    for (int i = 0; i < n; i++) {
  for (int j = tmp[i].w; j <= Max; j++) {
      if (dp[j]) {
    t = min(j - tmp[i].w, tmp[i].s);
    if (dp[t] < dp[j] + 1)
        dp[t] = dp[j] + 1;
      }
  }
  t = tmp[i].s - tmp[i].w;
  if (dp[t] == 0)
      dp[t] = 1;
    }

    int cur = 0;
    for (int i = 0; i <= Max; i++) {
  if (cur < dp[i])    cur = dp[i];
    }
    return cur;
}

int main() {
    Init();

    printf("%d\n", solve());
    return 0;
}
