#include <stdio.h>
#include <string.h>
#include <set>
#include <iostream>
using namespace std;
const int N = 55;

set<string> vec;
int g[N][N], n, flag;
char str[4][N * N];

void handle() {
    memset(str, 0, sizeof(str));
    int t = 0, k = 0;
    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        str[k][t++] = g[i][j] + '0';
    str[k++][t] = '\0';
    t = 0;

    for (int j = n - 1; j >= 0; j--)
    for (int i = 0; i < n; i++)
        str[k][t++] = g[i][j] + '0';
    str[k++][t] = '\0';
    t = 0;

    for (int j = 0; j < n; j++)
    for (int i = n - 1; i >= 0; i--)
        str[k][t++] = g[i][j] + '0';
    str[k++][t] = '\0';
    t = 0;

    for (int i = n - 1; i >= 0; i--)
    for (int j = n - 1; j >= 0; j--)
        str[k][t++] = g[i][j] + '0';

    str[k++][t] = '\0';
}

int main() {
    int x, y;
    char c;
    while (scanf("%d", &n), n) {
    memset(g, 0, sizeof(g));
    flag = 0;
    vec.clear();
    for (int i = 1; i <= 2 * n; i++) {
        scanf("%d%d %c", &x, &y, &c);

        if (c == '+')
        g[x - 1][y - 1] = 1;
        else if (c == '-')
        g[x - 1][y - 1] = 0;

        handle();

        if (!flag) {
        for (int j = 0; j < 4; j++) {
            if (vec.find(str[j]) != vec.end())
            flag = i;
        }
        }

        if (!flag) {
        for (int j = 0; j < 4; j++)
            vec.insert(str[j]);
        }
    }

    if (flag % 2)
        printf("Player 2 wins on move %d\n", flag);
    else if (flag)
        printf("Player 1 wins on move %d\n", flag);     
    else
        printf("Draw\n");
    }
    return 0;
}
