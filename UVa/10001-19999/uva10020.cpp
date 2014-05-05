#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1000005;

struct Seg {
    int x;
    int y;
}seg[N];
int n, cnt, order, vis[N];

bool cmp (const Seg& a, const Seg& b) {
    if (a.x != b.x)
  return a.x < b.x;
    else
  return a.y < b.y;
}

void input() {
    int p, q;
    n = cnt = 0;
    scanf("%d", &order);
    while (scanf("%d%d", &p, &q), p + q) {
  seg[n].x = p;
  seg[n].y = q;
  n++;
    }
}

int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
  memset(seg, 0, sizeof(seg));
  memset(vis, 0, sizeof(vis));
  input();

  sort(seg, seg + n, cmp);

  int begin = 0, Max, id;
  for (int i = 0; i < n; i++) {
      if (seg[i].x > order)   break;

      Max = 0, id;
      int k;
      for (k = 0; k < n - i; k++) {
    if (seg[i + k].x > begin) {
      k--;
      break;
    }
    if (seg[i + k].y > Max) {
        Max = seg[i + k].y;
        id = i + k;
    }
      }
      if (k > 0)
    i += k;
      if (Max < begin)  break;

      begin = Max; 
      vis[cnt++] = id;

      if (begin >= order)   break;
  }
  if (Max >= order) {
      printf("%d\n", cnt);
      for (int i = 0; i < cnt; i++)
    printf("%d %d\n", seg[vis[i]].x, seg[vis[i]].y);
  }
  else
      printf("0\n");
  if (cas)      printf("\n");
    }
    return 0;
}
