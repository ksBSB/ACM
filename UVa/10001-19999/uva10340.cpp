#include <stdio.h>
#include <string.h>

const int N = 1000005;
char f[N], s[N];
int n, m, vis[N];

bool solve(int a, int b) {
    if (b >= m) return true;

    for (int i = a; i < n; i++) {
  if (f[i] == s[b]) {
      if (solve(i + 1, b + 1))
    return true;
  }
    }
    return false;
}

int main() {
    while (scanf("%s%s", s, f) == 2) {
  n = strlen(f), m = strlen(s);
  printf("%s\n", solve(0, 0) ? "Yes" : "No");
    }
    return 0;
}
