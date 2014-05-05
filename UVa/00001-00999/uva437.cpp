#include <stdio.h>
#include <string.h>
const int N = 100005;

struct state {
    int r;
    int c;
    int h;
}tmp[N];
int n, dp[N];

void build(int k) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    k *= 3;
    tmp[k].r = a, tmp[k].c = b, tmp[k++].h = c;
    tmp[k].r = b, tmp[k].c = c, tmp[k++].h = a;
    tmp[k].r = c, tmp[k].c = a, tmp[k++].h = b;
}

int search(int k) {
    if (dp[k])  return dp[k];

    for (int i = 0; i < n; i++) {
  if ((tmp[k].r > tmp[i].r && tmp[k].c > tmp[i].c) || (tmp[k].r > tmp[i].c && tmp[k].c > tmp[i].r)) {
      if (dp[k] < search(i))  dp[k] = search(i);
  }
    }
    return dp[k] += tmp[k].h;
}

int solve() {
    n *= 3;
    int Max = 0;
    for (int i = 0; i < n; i++) {
  if (!dp[i]) search(i);
  if (Max < dp[i])    Max = dp[i];
    }
    return Max;
}

int main() {
    int cas = 1;
    while (scanf("%d", &n) == 1 && n) {
  // Init;
  memset(tmp, 0, sizeof(tmp));
  memset(dp, 0, sizeof(dp));

  // Read;
  for (int i = 0; i < n; i++)
      build(i);

  printf("Case %d: maximum height = %d\n", cas++, solve());
    }
    return 0;
}
