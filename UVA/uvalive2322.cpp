#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 5005;

struct stick {
    int len;
    int wei;
}tmp[N], rec[N];

bool cmp(const stick& a, const stick& b) {
    if (a.len != b.len)
  return a.len < b.len;
    else
  return a.wei < b.wei;
}

int main() {
    int cas, n, cnt, begin;
    scanf("%d", &cas);
    while (cas--) {
  cnt = 0;
  memset(tmp, 0, sizeof(tmp));
  memset(rec, 0, sizeof(rec));

  scanf("%d", &n);
  for (int i = 0; i < n; i++)
      scanf("%d %d", &tmp[i].len, &tmp[i].wei);

  sort(tmp, tmp + n, cmp);

  for (int i = 0; i < n; i++) {
      int flag = 1;
      for (int j = 0; j < cnt; j++) {
    if (tmp[i].len >= rec[j].len && tmp[i].wei >= rec[j].wei) {
        rec[j] = tmp[i];
        flag = 0;
        break;
    }
      }

      if (flag) rec[cnt++] = tmp[i];
  }
  printf("%d\n", cnt);
    }
    return 0;
}
