#include <stdio.h>
#include <string.h>
const int N = 1010;
int h, n, Max, s[N], d[N], dist[N];
int now[N], rec[N], vis[N];

void input() {
    int t;
    Max = 0;
    memset(s, 0, sizeof(s));
    memset(d, 0, sizeof(d));
    memset(dist, 0, sizeof(dist));
    memset(rec, 0, sizeof(rec));
    scanf("%d", &h);

    for (int i = 0; i < n; i++)
  scanf("%d", &s[i]);

    for (int i = 0; i < n; i++)
  scanf("%d", &d[i]);

    for (int i = 1; i < n; i++) {
  scanf("%d", &dist[i]);
  dist[i] += dist[i - 1];
    }
}

void output() {
    if (Max)
  printf("%d", rec[0] * 5);
    else
  printf("%d", h * 60);
    for (int i = 1; i < n; i++)
  printf(", %d", rec[i] * 5);
    printf("\nNumber of fish expected: %d\n", Max);
}

int find(int m) {
    int tmp = 0, id;
    for (int i = 0; i <= m; i++)
  if (tmp < now[i]) {
      tmp = now[i];
      id = i;
  }
    return tmp ? id : -1;
}

int solve() {
    int sum, time, id;

    for (int i = 0; i < n; i++) {
  time = h * 12 - dist[i];
  if (time <= 0)  break;
  memcpy(now, s, sizeof(s));
  memset(vis, 0, sizeof(vis));
  sum = 0;

  while (time > 0) {
      id = find(i);
      if (id < 0) break;
      time--;
      sum += now[id];
      now[id] -= d[id];
      vis[id]++;
  }
  if (time > 0)
      vis[0] += time;

  if (sum > Max) {
      Max = sum;
      memcpy(rec, vis, sizeof(vis));
  }
    }
}

int main() {
    int t, flag = 1;
    while (scanf("%d", &n) && n) {
  input();
  if (flag)   flag = 0;
  else 
      printf("\n");
  solve();
  output();
    }
    return 0;
}
