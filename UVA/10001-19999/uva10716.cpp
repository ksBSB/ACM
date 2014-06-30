#include <stdio.h>
#include <string.h>
const int N = 10010;

int len;
char tmp[N];

bool judge() {
    int vis[30], cnt = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < len; i++)
  vis[tmp[i] - 'a'] = !vis[tmp[i] - 'a'];
    for (int i = 0; i < 30; i++)
  cnt += vis[i];
    return cnt > 1;
}

void swap(int begin, int n, int sex) {
    char c;
    if (sex) {
  c = tmp[begin - n];
  for (int i = begin - n; i < begin; i++)
      tmp[i] = tmp[i + 1];
  tmp[begin] = c;
    }
    else {
  c = tmp[begin + n];
  for (int i = begin + n; i > begin; i--)
      tmp[i] = tmp[i - 1];
  tmp[begin] = c;
    }
}

int solve() {
    int left = 0, right = len - 1, cnt = 0;
    while(left < right) {
  if (tmp[left] != tmp[right]) {
      int l, r;
      for (l = 1; left + l <= right; l++)
    if (tmp[left + l] == tmp[right])   break;
      for (r = 1; right - r >= left; r++) 
    if (tmp[right - r] == tmp[left])    break;

      if (l > r) {
    cnt += r;
    swap(right, r, 1);
      }
      else {
    cnt += l;
    swap(left, l, 0);
      }
  }
  left++, right--;
    }
    return cnt;
}

int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
  memset(tmp, 0, sizeof(tmp));

  scanf("%s", tmp);
  len = strlen(tmp);

  if (judge())
      printf("Impossible\n");
  else
      printf("%d\n", solve());
    }
    return 0;
}
