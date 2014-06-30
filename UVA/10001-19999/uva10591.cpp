#include <stdio.h>
#include <string.h>

const int N = 10005;

int count(int cur) {
    int sum = 0, t;
    while (cur){    
    t = cur % 10;
    sum = sum + t * t;
    cur = cur / 10; 
    }
    return sum;
}

int main() {
    int cas = 1, n, m, cur;
    int v[N];
    scanf("%d", &m);
    while (m--) {
    scanf("%d", &n);
    memset(v, 0, sizeof(v));
    cur = n;
    while (1) {
        cur = count(cur);
        if (v[cur])
        break;
        v[cur] = 1;
    }
    printf("Case #%d: %d is %s number.\n", cas++, n, v[1]?"a Happy":"an Unhappy");
    }
    return 0;
}
