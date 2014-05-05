#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 500005;

struct que {
    int x;
    int y;
}tmp[N], rec[N];

bool cmp(const que &a, const que &b) {
    if(a.x < b.x)
  return true;
    else if (a.x > b.x)
  return false;
    else if (a.y < b.y)
  return true;
    else
  return false;
}

int main() {
    int n;
    while (scanf("%d", &n), n) {
  // Init;
  memset(tmp, 0, sizeof(tmp));
  memset(rec, 0, sizeof(rec));

  // Read;
  for (int i = 0; i < n; i++) {
      scanf("%d%d", &tmp[i].x, &tmp[i].y);
      rec[i].y = tmp[i].x;
      rec[i].x = tmp[i].y;
  }

  sort(tmp, tmp + n, cmp);
  sort(rec, rec + n, cmp);

  int flag = 1;
  for (int i = 0; i < n; i++)
      if (tmp[i].x != rec[i].x || tmp[i].y != rec[i].y) {
    flag = 0;
    break;
      }
  printf("%s\n", flag ? "YES" : "NO");
    }
    return 0;
}
