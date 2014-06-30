#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int max(const int &a, const int &b) { return a > b ? a : b; }
int min(const int &a, const int &b) { return a < b ? a : b; }
const int N = 10005;

int main() {
    int n, a, vis[N], pick[N];
    while (scanf("%d", &n), n) {
  int cnt = 0, Max = 0;
  memset(vis, 0, sizeof(vis));
  memset(pick, 0, sizeof(pick));

  for (int i = 0; i < n; i++) {
      scanf("%d", &pick[i]);
      Max = max(Max, pick[i]);
      cnt = max(cnt, ++vis[pick[i]]);
  }
  printf("%d\n", cnt);
  sort(pick, pick + n);

  for (int i = 0; i < cnt; i ++) {  
      for (int j = i; j < n; j += cnt) {  
    printf("%d", pick[j]);  
    if (j + cnt < n) printf(" ");  
    else printf("\n");  
      }  
  }  
    }
    return 0;
}
