#include <stdio.h>
#include <string.h>
const int N = 30005;
const int val[5] = {1, 5, 10, 25, 50};

long long cnt[N];

void Init() {
    memset(cnt, 0, sizeof(cnt));
    cnt[0] = 1;
    for (int i = 0; i < 5; i++) {
  for (int j = val[i]; j < N; j++)
      cnt[j] += cnt[j - val[i]];
    }
}

int main() {
    Init();
    int n;
    while (scanf("%d", &n) == 1) {
  if (cnt[n] <= 1)
      printf("There is only 1 way to produce %d cents change.\n", n);
  else
      printf("There are %lld ways to produce %d cents change.\n", cnt[n], n);
    }
    return 0;
}
