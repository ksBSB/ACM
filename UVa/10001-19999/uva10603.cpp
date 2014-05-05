#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int N = 205;

struct coor {
    int cup[3];
    int remove;
    coor(int c) {
    memset(cup, 0, sizeof(cup));
    this ->cup[2] = c;
    this -> remove = 0;
    }
};

int vis[N][N];
int Cup[3], order;
int mis[N];
const int dir[6][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};

int min(int a, int b) {
    return a > b?b:a;
}

bool judgeSome(coor cur) {
    for (int i = 0; i < 3; i++)
    if (cur.cup[i] == order)
        return true;
    return false;
}

int bfs() {
    queue<coor> que;
    coor now(Cup[2]), next(0);
    memset(mis, 0, sizeof(mis));
    memset(vis, 0, sizeof(vis));

    que.push(now);
    if (judgeSome(now))
    return now.remove;
    vis[0][0] = 1;
    mis[0] = 1;
    mis[Cup[2]] = 1;

    while (!que.empty()) {
    now = que.front();

    for (int i = 0; i < 6; i++) {
        next.cup[dir[i][0]] = min(now.cup[dir[i][0]] + now.cup[dir[i][1]], Cup[dir[i][0]]);
        next.cup[dir[i][1]] = now.cup[dir[i][1]] - next.cup[dir[i][0]] + now.cup[dir[i][0]];
        next.cup[dir[i][2]] = now.cup[dir[i][2]];
        next.remove = now.remove + next.cup[dir[i][0]] - now.cup[dir[i][0]];

        if (vis[next.cup[0]][next.cup[1]])  
        continue;
        if (judgeSome(next))
        return next.remove;

        vis[next.cup[0]][next.cup[1]] = 1;
        que.push(next);
        for (int i = 0; i < 3; i++)
        mis[next.cup[i]] = 1;
    }
    que.pop();
    }
    return -1;
}

int search() {
    for (int i = order; i >= 0; i++)
    if (mis[i])
        return i;
    return -1;
}

int main() {
    int cas, sum;
    scanf("%d", &cas);
    while (cas--) {
    for (int i = 0; i < 3; i++)
        scanf("%d", &Cup[i]);
    scanf("%d", &order);

    int sum = bfs();

    if(sum >= 0)
        printf("%d %d\n", sum, order);
    else
        printf("%d %d\n", search(), order);
    }
    return 0;
}
