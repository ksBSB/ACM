#include <stdio.h>
#include <string.h>
const int N = 10005;
long long dp[N];

void Init() {
    int t;
    dp[0] = 1;
    for (int i = 1; i <= 21; i++) {
  t = i * i * i;
  for (int j = t; j < N; j++)
      dp[j] += dp[j - t];
    }
}

int main() {
    Init();
    int n;
    while (scanf("%d", &n) == 1) {
  printf("%lld\n", dp[n]);
    }
    return 0;
}
