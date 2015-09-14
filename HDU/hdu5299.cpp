#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int maxn = 20005;
typedef long long ll;

struct Circle {
    int x, y, r;
    void input() {
        scanf("%d%d%d", &x, &y, &r);
    }
}C[maxn];

int N, Nim[maxn];
vector<int> G[maxn];

inline bool cmp(const Circle& a, const Circle& b) {
    return a.x < b.x;
}

inline int distance(int a, int b) {
    return a * a + b * b;
}

bool judge(const Circle& a, const Circle& b) {
    return (a.r > b.r) && distance(a.x - b.x, a.y - b.y) < a.r * a.r;
}

int fa[maxn];

void init () {

    scanf("%d", &N);
    memset(Nim, -1, sizeof(Nim));
    for (int i = 0; i < N; i++) {
        fa[i] = i;
        C[i].input();
        G[i].clear();
    }

    sort(C, C + N, cmp);

    for (int i = 0; i < N; i++) {
       for (int j = i + 1; j < N && C[j].x - C[i].x <= C[i].r; j++) {
           if (judge(C[i], C[j])) {
               if (fa[j] == j) fa[j] = i;
               else {
                   if (C[i].r < C[fa[j]].r) fa[j] = i;
               }
           }
       }
       for (int j = i - 1; j >= 0 && C[i].x - C[j].x <= C[i].r; j--) {
           if (judge(C[i], C[j])) {
               if (fa[j] == j) fa[j] = i;
               else {
                   if (C[i].r < C[fa[j]].r) fa[j] = i;
               }
           }
       }
    }
    for (int i = 0; i < N; i++) {
        if (fa[i] != i)
            G[fa[i]].push_back(i);
    }
}

int SG(int u) {
    if (Nim[u] != -1)
        return Nim[u];

    int& ret = Nim[u];
    ret = 0;
    for (int i = 0; i < G[u].size(); i++)
        ret ^= SG(G[u][i]);
    ret += 1;
    return ret;
}

int main () {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        init();
        int ans = 0;
        for (int i = 0; i < N; i++) {
            if (fa[i] == i)
                ans ^= SG(i);
        }
        printf("%s\n", ans ? "Alice" : "Bob");
    }
    return 0;
}
