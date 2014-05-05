#include <stdio.h>
#include <string.h>
const int N = 10005;

int a, b, sum, dp[N * 2];

void solve() {
    memset(dp, 0, sizeof(dp));
    dp[a] = 1;
    for (int i = 0; i < N; i++)
       if (dp[i] && dp[i] + 1 > dp[i + a])
      dp[i + a] = dp[i] + 1;     
    dp[b] = 1;
    for (int i = 0; i < N; i++)
  if(dp[i] && dp[i] + 1 > dp[i + b])
      dp[i + b] = dp[i] + 1;
}

int main() {
    while (scanf("%d%d%d", &a, &b, &sum) == 3) {
  int flag = 1;
  solve();
  for (int i = 0; i <= sum; i++)
      if (dp[sum - i]) {
    printf("%d", dp[sum - i]);
    if (i)
        printf(" %d", i);
    printf("\n");
    flag = 0;
    break;
      }
  if (flag)
      printf("0 %d\n", sum);
    }
    return 0;
}
