#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int maxn = 205;
const int INF = 0x7f7f7f7f;
const int dir[6][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};

struct state {
    int cup[3];
    int step;
    state (int a = 0, int b = 0, int c = 0, int step = 0) {
        this->cup[0] = a;
        this->cup[1] = b;
        this->cup[2] = c;
        this->step = step;
    }
};
int Cup[3], D, d[maxn][maxn];

bool add_state (state u) {
    if (d[u.cup[0]][u.cup[1]] > u.step) {
        d[u.cup[0]][u.cup[1]] = u.step;
        return true;
    }
    return false;
}

void BFS () {
    state s(0, 0, Cup[2], 0);
    queue<state> que;

    que.push(s);

    while (!que.empty()) {
        state u = que.front();
        que.pop();
        if (!add_state(u))
            continue;

        for (int i = 0; i < 6; i++) {
            state k;
            k.cup[dir[i][0]] = min(u.cup[dir[i][0]] + u.cup[dir[i][1]], Cup[dir[i][0]]);  
            k.cup[dir[i][1]] = u.cup[dir[i][1]] - k.cup[dir[i][0]] + u.cup[dir[i][0]];  
            k.cup[dir[i][2]] = u.cup[dir[i][2]]; 
            k.step = u.step + k.cup[dir[i][0]] - u.cup[dir[i][0]]; 

            que.push(k);
        }
    }
}

bool search (int x) {
    int ans = INF;
    for (int i = 0; i <= Cup[2] - x; i++) {
        ans = min(ans, d[x][i]);
        ans = min(ans, d[i][x]);
        ans = min(ans, d[i][Cup[2] - x - i]);
    }

    if (ans == INF)
        return false;
    printf("%d %d\n", ans, x);
    return true;
}

int main () {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d%d%d", &Cup[0], &Cup[1], &Cup[2], &D);

        memset(d, INF, sizeof(d));
        BFS();

        for (int i = D; i >= 0; i--) {
            if (search(i))
                break;
        }
    }
    return 0;
}
