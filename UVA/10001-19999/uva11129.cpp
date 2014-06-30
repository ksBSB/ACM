#include <stdio.h>
#include <string.h>
const int N = 10010;
int n, ans[N];

void solve(int begin, int end) {
    if (begin == end) return;
    int tmp[N], pos = begin;
    memcpy(tmp, ans, sizeof(ans));
    for (int i = begin; i <= end; i += 2)
  ans[pos++] = tmp[i];
    for (int i = begin + 1; i <= end; i += 2)
  ans[pos++] = tmp[i];
    solve(begin, (begin + end) / 2);
    solve((begin + end) / 2 + 1, end); 
}

void output() {
    printf("%d:", n);
    for (int i = 0; i < n; i++)
  printf(" %d", ans[i]);
    printf("\n");
}

int main() {
    while (scanf("%d", &n), n) {
  for (int i = 0; i < n; i++)
      ans[i] = i;
  solve(0, n - 1);
  output();
    }
    return 0;
}
