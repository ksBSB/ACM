#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 300;

char str[N];
string file[N];
int vis[N], len, n;
string order;

bool cmp(const string &a, const string &b) {
    return a.length() < b.length();
}

bool solved(int cur) {
    if (cur >= n / 2)
  return true;

    vis[cur] = 1;
    int l = file[cur].length();
    for (int i = n - 1; i >= 0; i--) {
  if (vis[i])   continue;
  if (l + file[i].length() > len)   return true;
  if (l + file[i].length() < len)   return false;
  string p, q;
  p = file[cur] + file[i];
  q = file[i] + file[cur];
  if (p == order || q == order) {
      vis[i] = 1;
      if (solved(cur + 1))
    return true;
      vis[i] = 0;
  }
    }
    vis[cur] = 0;
    return false;
}

int main() {
    int cas, sum, max;
    scanf("%d%*c%*c", &cas);
    while (cas--) {
  sum = n = 0;
  memset(vis, 0, sizeof(vis));

  while (gets(str)) {
      if (!str[0])  break;
      file[n] = str;
      sum += file[n++].length();
  }

  sort(file, file + n, cmp);
  len = sum * 2 / n;
  vis[0] = 1;
  for (int i = n - 1; i >= 0; i--) {
      vis[i] = 1;
      order.clear();
      order = file[0] + file[i];
      if (solved(1))  break;

      order.clear();
      order = file[i] + file[0];
      if (solved(1))  break;
      vis[i] = 0;
  }
  cout << order << endl;
  if (cas)
      cout << endl;
    }
    return 0;
}
