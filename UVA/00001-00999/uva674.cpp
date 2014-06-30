#include <stdio.h>
#include <string.h>
const int N = 7500;
const int sex[] = {1, 5, 10, 25, 50};

int n, cnt[N], t;

void Init() {
    memset(cnt, 0, sizeof(cnt));
    cnt[0] = 1;
    for (int i = 0; i < 5; i++) {
  for (int j = sex[i]; j < N; j++)
      cnt[j] += cnt[j - sex[i]];
    }
}

int main() {
    Init();
    while (scanf("%d", &n) == 1) {
  printf("%d\n", cnt[n]);
    }
    return 0;
}
