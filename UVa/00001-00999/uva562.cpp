#include <stdio.h>
#include <string.h>
const int N = 50005;
const int M = 105;

int n, sum, dp[N], coin[M], Max;

int solve() {
    memset(dp, 0, sizeof(dp));
    dp[0]= 1;
    int half = sum / 2;

    for (int i = 0; i < n; i++) {
  for (int j = half - 1; j >= 0; j--)
      if (dp[j])  dp[j + coin[i]] = 1;
    }

    for (int i = 0; i <= half; i++)
  if (dp[half - i])   return i * 2;
}

int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
  sum = 0;
  scanf("%d", &n);
  memset(coin, 0, sizeof(coin));
  for (int i = 0; i < n; i++) {
      scanf("%d", &coin[i]);
      sum += coin[i];
  }
  printf("%d\n", solve() + sum % 2);
    }
    return 0;
}
