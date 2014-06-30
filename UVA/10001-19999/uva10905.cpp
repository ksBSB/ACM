#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1005;

struct number {
    char s[N]; 
}num[N];

bool cmp(const number &a, const number &b) {
   char str1[N], str2[N];
   strcpy(str1, a.s);
   strcat(str1, b.s);
   strcpy(str2, b.s);
   strcat(str2, a.s);
   return strcmp(str1, str2) > 0;
}

int main() {
    int n;
    while (scanf("%d", &n), n) {
    // Init;
    memset(num, 0, sizeof(num));

    // Read;
    for (int i = 0; i < n; i++)
        scanf("%s", num[i].s);

    sort(num, num + n, cmp);

    for (int i = 0; i < n; i++)
        printf("%s", num[i].s);
    printf("\n");
    }
    return 0;
}
