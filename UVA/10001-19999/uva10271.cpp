#include <stdio.h>
#include <string.h>
const int N = 5010;
const int MAX = 0x3f3f3f3f;
int min(int a, int b) { return a > b ? b : a; }

int val[N], dp[N][1010];

int P(int a) {
    return a * a;
}

int main () {
    int cas, n, m;
    scanf("%d", &cas);
    while (cas--) {
  scanf("%d%d", &m, &n);
  memset(dp, MAX, sizeof(dp));

  m += 8;
  dp[0][0] = 0;
  for (int i = 1; i <= n; i++) {
      scanf("%d", &val[i]);
      dp[i][0] = 0;
  }

  for (int i = n - 2; i >= 1; i--) {
      for (int j = m; j >= 1; j--) {
    dp[i][j] = dp[i + 1][j];
    if (dp[i + 2][j - 1] != MAX && n - i - j * 3 >= -1)
        dp[i][j] = min(dp[i][j], dp[i + 2][j - 1] + P(val[i] - val[i + 1]));
      }
  }
  printf("%d\n", dp[1][m]);
    }
    return 0;
}
