#include <stdio.h>
#include <string.h>
const int N = 1005;
char str[N];

bool dp(int a, int b) {
    if (a == b)
  return str[a] == 'A' ? true : false;
    else if (str[b - 1] == 'A' && str[b] == 'B')
  return dp(a, b - 2) ? true : false;
    else if (str[a] == 'B' && str[b] == 'A')
  return dp(a + 1, b - 1) ? true : false;
    return false;
}

int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
  scanf("%s", str);
  int len = strlen(str) - 1;
  if (len == 0 && str[0] == 'A')
      printf("SIMPLE\n");
  else if (str[len - 1] == 'A' && str[len] == 'B' && dp(0, len - 2))
      printf("FULLY-GROWN\n");
  else if (str[0] == 'B' && str[len] == 'A' && dp(1, len - 1))
      printf("MUTAGENIC\n");
  else
      printf("MUTANT\n");
    }
    return 0;
}
