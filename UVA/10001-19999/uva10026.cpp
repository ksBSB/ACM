#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1005;

struct State {
    int id;
    int day;
    int val;
}num[N];

bool cmp(const State &a, const State &b) {
    return a.val * b.day > b.val * a.day;
}

int main() {
    int cas, n;
    scanf("%d", &cas);
    while (cas--) {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
      num[i].id = i + 1;
      scanf("%d%d", &num[i].day, &num[i].val);
  }
  sort(num, num + n, cmp);
  for (int i = 0; i < n - 1; i++)
      printf("%d ", num[i].id);
  printf("%d\n", num[n -1].id);
  if (cas)
      printf("\n");
    }
    return 0;
}
