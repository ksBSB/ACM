#include <stdio.h>
#include <stdlib.h>
const int N = 1000005;

int num[N];
int main() {
    int n;
    while (scanf("%d", &n), n) {
  for (int i = 0; i < n; i++)
      scanf("%d", &num[i]);

  long long sum = 0;
  for (int i = 0; i < n - 1; i++) {
      sum += abs(num[i]);
      num[i + 1] += num[i];
  }
  printf("%lld\n", sum);
    }
    return 0;
}
