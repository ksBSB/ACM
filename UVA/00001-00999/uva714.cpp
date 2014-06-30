#include <stdio.h>
#include <string.h>
int max(const int &a, const int &b) { return a > b ? a : b;}

const int N = 1005;
int n, T;
long long num[N], sum[N], rec[N];

bool judge(int Max) {
    int cnt = 0, first = 0, end = 1;
    while (end <= n) {
  if (sum[end] - sum[first] > Max) {
      cnt++;
      first = end - 1;
  }
  end++;
    }
    return cnt <= T - 1;
}

int main () {
    long long  cas, lift, right, cur;
    scanf("%lld", &cas);
    while (cas--) {
  // Init;
  memset(num, 0, sizeof(num));
  memset(sum, 0, sizeof(sum));
  memset(rec, 0, sizeof(rec));
  lift = right = 0;

  // Read.
  scanf("%d%d", &n, &T);
  for (int i = 1; i <= n; i++) {
      scanf("%lld", &num[i]);
      sum[i] = sum[i - 1] + num[i];
      lift = max(lift, num[i]);
  }
  right = sum[n];

  // Count;
  while (lift != right) {
      cur = (right + lift) / 2;
      if (judge(cur)) {
    right = cur;
      }
      else
    lift = cur + 1;
  }

  // Draw;
  long long now = 0, cnt = 0;
  for (int i = n; i > 0; i--) {
      if (now + num[i] > lift || i < T - cnt) {
    rec[i] = 1;
    cnt++;
    now = num[i];
      }
      else
    now += num[i];
  }

  // Printf;
  for (int i = 1; i < n; i++) {
      printf("%lld ", num[i]);
      if (rec[i])     printf("/ ");
  }
  printf("%lld\n", num[n]);
    }
    return 0;
}
