#include <stdio.h>
#include <stdlib.h>
const int N = 350000;
const int MAX = 2147483647;
const int w[] = {0, 10, 100, 1000, 10000, 100000};

int n = 2, num[N];
long long sum[N];

void init() {
    sum[0] = num[0] = 0, sum[1] = num[1] = 1;
    for (int cur = 1; sum[n - 1] < MAX; n++) {
  if (n >= w[cur])    cur++;
  sum[n] = sum[n - 1] * 2 - sum[n - 2] + cur;
  num[n] = sum[n] - sum[n - 1];
    }
}

int main () {
    init();
    int cas, tmp, cur;
    char str[10];
    scanf("%d", &cas);
    while (cas--) {
  scanf("%d", &tmp);
  for (cur = 1; cur < n; cur++)
      if(tmp <= sum[cur])    break;
  tmp -= sum[cur - 1];
  for (cur = 1; cur < n; cur++) 
      if (tmp <= num[cur])    break;
  tmp -= num[cur - 1];
  sprintf(str, "%d", cur);
  printf("%c\n", str[--tmp]);
    }
    return 0;
}
