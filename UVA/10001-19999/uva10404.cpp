#include <stdio.h>
#include <string.h>
const int N = 1000005;

int n, m, dp[N], val[20];

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
  memset(dp, 0, sizeof(dp));
  memset(val, 0, sizeof(val));
  for (int i = 0; i < m; i++)
      scanf("%d", &val[i]);

  for (int i = 1; i <= n; i++) {
      for (int j = 0; j < m; j++)
    if (i - val[j] >= 0 && !dp[i - val[j]]) {
        dp[i] = 1;
        break;
    }
  }
  printf("%s\n", dp[n] ? "Stan wins" : "Ollie wins");
    }
    return 0;
}
