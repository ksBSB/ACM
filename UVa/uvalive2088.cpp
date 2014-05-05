#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
const int N = 10005;

struct Node {
    int r;
    int l;
    int cnt;
    bool operator < (const Node& a) const {
        return cnt > a.cnt;
    }
}tmp[N];

int len, sum, vis[N];

void init(char str[]) {
    memset(tmp, 0, sizeof(tmp));
    memset(vis, 0, sizeof(vis));
    sum = 0;
    len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        if (str[i] == '_')
            vis[26]++;
        else
            vis[str[i] - 'A']++;
    }
}

void count(Node cur, int deep) {
    if (cur.l == -1 && cur.r == -1) {
        sum += deep * cur.cnt;
  return;
    }
    if (cur.l != -1)   
  count(tmp[cur.l], deep + 1);
    if (cur.r != -1)
  count(tmp[cur.r], deep + 1);
}

void solve() {
    int n = 0;
    Node now;
    priority_queue<Node> que;
    for (int i = 0; i < 27; i++)
  if (vis[i]) {
      now.cnt = vis[i];
      now.l = now.r = -1;
      que.push(now);
  }

    while (1) {
  tmp[n++] = que.top(),    que.pop();
  if (que.empty())    break;
  tmp[n++] = que.top(),    que.pop();
  now.cnt = tmp[n - 1].cnt + tmp[n - 2].cnt;
  now.l = n - 1, now.r = n - 2;
  que.push(now);
    }
    if (n == 1)
  sum = tmp[n - 1].cnt;
    else
  count(tmp[n - 1], 0);
}

int main() {
    char str[N];
    while (scanf("%s", str) == 1) {
  if (strcmp(str, "END") == 0)  break;

  init(str);
  solve();
  printf("%d %d %.1lf\n", len * 8, sum, len * 8.0 / sum);
    }
    return 0;
}
