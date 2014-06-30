#include <stdio.h>
#include <string.h>
const int N = 30005;
const int val[11] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};

long long n, dp[N];

void solve() {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 0; i < 11; i++) {
  for (int j = val[i]; j < N; j++)
      dp[j] += dp[j - val[i]];
    }
}

int main () {
    solve();
    double f;
    while (scanf("%lf", &f) == 1) {
  n = (f + 0.005) * 100;
  if (!n) break;
  printf("%6.2lf%17lld\n", f, dp[n]);
    }
    return 0;
}
