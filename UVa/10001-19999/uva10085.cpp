#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

typedef int State[20];
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const int MAXN = 1000005;
const char sign[5] = "UDLR";

int dis[MAXN], goal;
int front, rear;
State st[MAXN];
char str[MAXN][100];
int head[MAXN], next[MAXN];

int hash(State& s) {
    int v = 0;
    for (int i = 0; i < 9; i++)
    v = v * 10 + s[i];
    return v % MAXN;
}

bool tryInsert(int s) {
    int h = hash(st[s]);
    int u = head[h];

    while (u) {
    if (memcmp(st[u], st[s], sizeof(st[s])) == 0)
        return false;
    u = next[u];
    }
    next[s] = head[h];
    head[h] = s;
    return true;
}

int bfs() {
    dis[1] = 0;
    while (front < rear) {
    State& now = st[front];
    int z;
    for (z = 0; z < 9; z++)
        if (!now[z])    break;
    int x = z / 3, y = z % 3;
    for (int i = 0; i < 4; i++) {
        int newx = x + dx[i];
        int newy = y + dy[i];
        int newz = newx * 3 + newy;
        if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {
        State& net = st[rear];

        for (int j = 0; j < 9; j++)
            net[j] = now[j];
        net[newz] = now[z];
        net[z] = now[newz];

        for (int j = 0; j < dis[front]; j++)
            str[rear][j] = str[front][j];
        str[rear][dis[front]] = sign[i];
        dis[rear] = dis[front] + 1;
        if (tryInsert(rear))    rear++;
        }
    }
    front++;
    }
}

int main() {

    int order[9], cas, t = 1;
    scanf("%d", &cas);
    while (cas--) {
    for (int i = 0; i < 9; i++)
        scanf("%d", &order[i]);

    front = 1;
    rear = 2;
    memset(st, 0, sizeof(st));
    memset(dis, 0, sizeof(dis));
    memset(str, 0, sizeof(str));
    memset(head, 0, sizeof(head));
    memset(next, 0, sizeof(next));
    memcpy(st[front], order, sizeof(order));
    bfs();
    rear--;

    printf("Puzzle #%d\n", t++ );
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++)
        printf("%d ", st[rear][i * 3 + j]);
        printf("%d\n", st[rear][i * 3 + 2]);
    }
    str[rear][dis[rear]] = '\0';
    puts(str[rear]);
    printf("\n");
    }
    return 0;
}
