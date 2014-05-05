#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 20;
const int N = 20005;
int nRoom, nDoor, nOpen;
int inDoor[MAXN][MAXN], sonDoor[MAXN];
int inOpen[MAXN][MAXN], sonOpen[MAXN];

struct Move {
    int room[MAXN];
    int order[400][2];
    int cnt;
}aid, que[N];
int dis[N];
const int begin[MAXN] = {0, 2, 0};
int end[MAXN];
int head[N], next[N];

void inInit() {
    memset(dis, 0, sizeof(dis));
    memset(que, 0, sizeof(que));
    memset(end, 0, sizeof(end));
    memset(head, 0, sizeof(head));
    memset(next, 0, sizeof(next));
    end[nRoom] = 2;
}

int hash(Move& s) {
    int sum = 0;
    for (int i = 1; i <= nRoom; i++)
        sum = sum * 5 + s.room[i];
    return sum % N;
}

bool tryInsert(Move& s, int cur) {
    int h = hash(s);
    int u = head[h];
    
    while (u) {
        if (memcmp(que[u].room, s.room, sizeof(s.room)) == 0)
            return false;
        u = next[u];
    }
    next[cur] = head[h];
    head[h] = cur;
    return true;
}

int bfs() {
    inInit();
    memcpy(que[1].room, begin, sizeof(begin));
    int front = 1, rear = 2;
    
    while (front < rear) {
        Move& now = que[front];
        
        if (memcmp(now.room, end, sizeof(end)) == 0) {
            aid = now;
            return now.cnt;
        }
        int x;
        for (x = 1; x < nRoom; x++)
            if (now.room[x] == 2)
                break;
        for (int i = 0; i < sonDoor[x]; i++) {
            if (now.room[inDoor[x][i]] == 1) {
                Move net = now;
                net.room[x] = 1;
                net.room[inDoor[x][i]] = 2;
                if (tryInsert(net, rear)) {
                    net.order[net.cnt][0] = 1;
                    net.order[net.cnt][1] = inDoor[x][i];
                    net.cnt++;
                    que[rear++] = net;
                }
            }
        }
        
        for (int i = 0; i < sonOpen[x]; i++) {
            Move net = now;
            net.room[inOpen[x][i]] = net.room[inOpen[x][i]]?0:1;
            if (tryInsert(net, rear)) {
                net.order[net.cnt][0] = net.room[inOpen[x][i]]?3:2;
                net.order[net.cnt][1] = inOpen[x][i];
                net.cnt++;
                if (memcmp(net.room, end, sizeof(end)) == 0) {
                    aid = net;
                    return net.cnt;
                }
                que[rear++] = net;
            }
        }
        front++;
    }
    return -1;
}

int main() {
    int a, b, cas = 1;
    while (scanf("%d%d%d", &nRoom, &nDoor, &nOpen), nRoom + nDoor + nOpen) {
        // Init;
        memset(sonDoor, 0, sizeof(sonDoor));
        memset(sonOpen, 0, sizeof(sonOpen));
        memset(inDoor, 0, sizeof(inDoor));
        memset(inOpen, 0, sizeof(inOpen));
        
        // Read;
        for (int i = 0; i < nDoor; i++) {
            scanf("%d%d", &a, &b);
            inDoor[a][sonDoor[a]++] = b;
            inDoor[b][sonDoor[b]++] = a;
        }
        for (int i = 1; i <= nOpen; i++) {
            scanf("%d%d", &a, &b);
            inOpen[a][sonOpen[a]++] = b;
        }


    for (int i = 1; i <= nRoom; i++) {
        sort(inDoor[i], inDoor[i] + sonDoor[i]);
        sort(inOpen[i], inOpen[i] + sonOpen[i]);
    }
    int flag = bfs();

    printf("Villa #%d\n", cas++);
    if (flag >= 0) {
        printf("The problem can be solved in %d steps:\n", flag);
        for (int i = 0; i < aid.cnt; i++) {
        if (aid.order[i][0] == 3)
            printf("- Switch on light in room %d.\n", aid.order[i][1]);
        else if (aid.order[i][0] == 2)
            printf("- Switch off light in room %d.\n", aid.order[i][1]);
        else
            printf("- Move to room %d.\n", aid.order[i][1]);
        }
    }
    else
        printf("The problem cannot be solved.\n");
    printf("\n");
    }
    return 0;
}
