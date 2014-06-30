#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 105;

struct company {
    char name[N];
    int one;
    int half;
    int value;
}tmp[N];
char str[N];
int tol, sur;

bool cmp(const company &a, const company &b) {
    if (a.value < b.value)  return true;
    else if (a.value > b.value) return false;
    else
  return strcmp(a.name, b.name) < 0;
}

int count(int t, int h) {
    int sum = tol, cur = 0;
    while (sum != sur) {
  int w = (sum + 1) / 2;
  if (t * w > h && sum - w >= sur) {
      sum -= w;
      cur += h;
  }
  else {
      sum--;
      cur += t;
  }
    }
    return cur;
}

void handle(int cur) {
    int len = strlen(str), cnt = 0, sex = 0;
    for (int i = 0; i < len; i++) {
  if (sex == 0 && str[i] != ':')
      tmp[cur].name[cnt++] = str[i];
  else if (str[i] == ':') {
      tmp[cur].name[cnt++] = '\0';
      sex++;
  }
  else if (sex == 1 && str[i] != ',')
      tmp[cur].one = tmp[cur].one * 10 + str[i] - '0';
  else if (str[i] == ',')
      sex++;
  else
      tmp[cur].half = tmp[cur].half * 10 + str[i] - '0';
    }
    tmp[cur].value = count(tmp[cur].one, tmp[cur].half);
}

int main() {
    int cas, t = 1, n;
    scanf("%d", &cas);
    while (cas--)  {
  memset(tmp, 0, sizeof(tmp));
  scanf("%d%d%d%*c", &tol, &sur, &n);
  for (int i = 0; i < n; i++) {
      gets(str);
      handle(i);
  }

  sort(tmp, tmp + n, cmp);

  printf("Case %d\n", t++);
  for (int i = 0; i < n; i++)
      printf("%s %d\n", tmp[i].name, tmp[i].value);
    }
    return 0;
}
