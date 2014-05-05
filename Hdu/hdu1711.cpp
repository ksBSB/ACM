#include <stdio.h>
#include <string.h>

const int N = 1000005;

int n, m, a[N], b[N], next[N], i;

void init () {
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (i = 1; i <= m; i++)
        scanf("%d", &b[i]);

    int p = 0;
    for (i = 2; i <= m; i++) {
        while (p > 0 && b[p+1] != b[i])
            p = next[p];
        
        if (b[p+1] == b[i])
            p++;
        next[i] = p;
    }
}

int KMP () {

    int p = 0;
    for (i = 1; i <= n; i++) {
        while (p > 0 && b[p+1] != a[i])
            p = next[p];

        if (b[p+1] == a[i])
            p++;

        if (p == m) {
            return i - m + 1;
        }
    }
    return -1;
}

int main () {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        init ();
        printf("%d\n", KMP());
    }
    return 0;
}