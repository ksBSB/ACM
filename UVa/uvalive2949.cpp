#include <stdio.h>
#include <string.h>
const int N = 32;

int n, mid, top, cnt, vis[N], stop[N];

void read() {
    int t;
    top = 0;
    memset(vis, 0, sizeof(vis));

    for (int i = 0; i < n; i++) {
  scanf("%d", &t);
  vis[t] = 1;
  if (t > top)  top = t;
    }
}

bool judge(int tmp) {
    cnt = 0;
    memset(stop, 0, sizeof(stop));

    for (int i = tmp / 20 + 2; i <= top; i++) {
  while (!vis[i] && i < top)  i++;
  int t = (i - 1) * 4 + cnt * 10;
  if (tmp < t)  return false;
  t = (tmp - 10 * cnt + 20 * i + 4) / 24;
  i = (tmp - 10 * cnt + 16 * t + 4) / 20;
  stop[cnt++] = t;
    }
    return true;
}

int solve() {
    int L = 0, R = 14 * (top - 1);
    while (L < R) {
  mid = (L + R + 1) / 2;
  if (mid == R) break;
  if (judge(mid))
      R = mid;
  else
      L = mid;
    }
    return mid;
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
  read();

  judge(solve());

  printf("%d\n%d", mid, cnt);
  for (int i = 0; i < cnt; i++)
      printf(" %d", stop[i]);
  printf("\n");
    }
    return 0;
}
