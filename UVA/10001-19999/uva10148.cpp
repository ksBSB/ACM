#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 10000;

struct way {
    int x;
    int y;
}w[N];
int sum, n, Min, Max, cnt, vis[N * 2 + 10];

bool cmp(const way& a, const way&b) {
    if (a.y != b.y) return a.y < b.y;
    else    return a.x > b.x;
}

void input() {
    Min = 1 < 30, Max = 0;
    int p, q;
    scanf("%d%d", &sum, &n);
    for (int i = 0; i < n; i++) {
  scanf("%d%d", &p, &q);
  if (p > q)
      w[i].x = q, w[i].y = p;
  else
      w[i].x = p, w[i].y = q;
  if (w[i].y > Max)   Max = w[i].y;
  if (w[i].x < Min)   Min = w[i].x;
    }
}

int solve() {
    int cnt = 0, now;
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++) {
  now = 0;
  for (int j = w[i].x; j <= w[i].y; j++)
      if (vis[j + N]) now++;

  now = sum - now;

  for (int j = w[i].y; j >= w[i].x && now > 0; j--)
      if (vis[j + N] == 0) {
    vis[j + N] = 1;
    now--;
    cnt++;
      }
    }
    return cnt;
}

int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
  input();
  sort(w, w + n, cmp);

  printf("%d\n", solve());
  for (int i = Min; i <= Max; i++)
      if (vis[i + N]) printf("%d\n", i);

  if (cas)    printf("\n");
    }
    return 0;
}
