#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const char begin[5][5] = {'1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '0', '0', ' ', '1', '1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0'};
const int dx[] = {-2, -2, 2, 2, -1, 1, -1, 1};
const int dy[] = {-1, 1, -1, 1, -2, -2, 2, 2};

char r[5][5];
int ans;
bool flag;

int diff() {
    int sum = 0;
    for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
        sum += (r[i][j] != begin[i][j]);
    return sum / 2;
}

void dfs(int deep, int x, int y) {
    if (deep >= ans) {
    if (memcmp(r, begin, 25 * sizeof(char)) == 0)
        flag = true;
    return;
    }
    if (deep + diff() > ans)
    return ;
    int swap;
    for (int i = 0; i < 8 && !flag; i++) {
    int newX = x + dx[i], newY = y + dy[i];
    if (newX < 0 || newX >= 5 || newY < 0 || newY >= 5)
        continue;

    swap = r[x][y];
    r[x][y] = r[newX][newY];
    r[newX][newY] = swap; 

    dfs(deep + 1, newX, newY);

    swap = r[x][y];
    r[x][y] = r[newX][newY];
    r[newX][newY] = swap; 
    }
}

int main() {
    int cas;
    scanf("%d%*c", &cas);
    while (cas--) {
    int x, y;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
        scanf("%c", &r[i][j]);
        if (r[i][j] == ' ') {
            x = i;
            y = j;
        }
        }
        getchar();
    }

    flag = 0;
    for (ans = 0; ans <= 10; ans++) {
        dfs(0, x, y);
        if (flag)
        break;
    }

    if (flag)
        printf("Solvable in %d move(s).\n", ans);
    else
        printf("Unsolvable in less than 11 move(s).\n");
    }
return 0;
}
