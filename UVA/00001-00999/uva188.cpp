#include <stdio.h>
#include <string.h>

const int N = 10005;
int n, flag, order, w[N];

int min(int a, int b) {
    return a < b ? a : b;
}

int judge(int cur) {
    for (int i = 0; i <= n; i++)
    for (int j = i + 1; j <= n; j++) {
        if (w[i] == 0 || w[j] == 0) continue;
        if ((cur / w[i]) % (n + 1) == (cur / w[j]) % (n + 1))
        return min((cur / w[i] + 1) * w[i], (cur / w[j] + 1) * w[j]); 
    }
    flag = 1;
    return cur;
}
void handle(char str[]) {
    n = 0;
    memset(w, 0, sizeof(w));
    int len = strlen(str);
    for (int i = 0; i < len; i ++) {
    if (str[i] == ' ')
        n++;   
    else
        w[n] = w[n] * 32 + (str[i] - 'a' + 1);
    }
}

int main() {
    char str[N];
    while (gets(str)) {
    handle(str);

    flag = 0;
    order = 999999999;

    for (int i = 0; i <= n; i ++) {
        if (order > w[i])
        order = w[i];
    }

    while (!flag) {
        order = judge(order);
    }
    puts(str);
    printf("%d\n\n", order);
    }
    return 0;
}
