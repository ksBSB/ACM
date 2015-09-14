#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
typedef pair<int,int> pii;

int N, M, F[maxn * 3], D[maxn * 3], P[maxn * 3], Vis[maxn * 3];
vector<pii> G[maxn];

void init () {
    memset(F, -1, sizeof(F));
    memset(D, 0, sizeof(D));
    memset(P, 0, sizeof(P));
    memset(Vis, 0, sizeof(Vis));

    int u, v;
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++)
        G[i].clear();

    for (int i = 1; i <= M; i++) {
        scanf("%d%d", &u, &v);
        G[u].push_back(make_pair(v, i));
        G[v].push_back(make_pair(u, -i));
    }
}

void set (int idx, int k) {
	if (idx < 0) {
		idx *= -1;
		k ^= 1;
	}
	F[idx] = k;
}

int dfs (int u) {

    if (Vis[u])
        return u;

    Vis[u] = 1;

    for (int& i = P[u]; i < G[u].size(); i++) {
        int v = G[u][i].first;
        int idx = G[u][i].second;
        if (F[abs(idx)] != -1)
            continue;

        F[abs(idx)] = -2;
        int k = dfs(v);
        F[abs(idx)] = -1;

        if (k) {
			set(idx, 1);
            if (k != u) {
                Vis[u] = 0;
                return k;
            }
		}
	}

	Vis[u] = 0;
	return 0;
}

void dfs (int u, int d) {
	Vis[u] = 1;
	int tmp = d;

	for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].first;
        int idx = G[u][i].second;
        if (F[abs(idx)] != -1)
            continue;

		set(idx, tmp);
		dfs(v, tmp);
		tmp ^= 1;
	}
}

void solve () {
	for (int i = 1; i <= N; i++) {
		if (P[i] != G[i].size())
			dfs(i);
	}

	for (int i = 1; i <= N; i++) {
		if (Vis[i])
			continue;
		dfs(i, 1);
	}

	for (int i = 1; i <= M; i++)
		printf("%d\n", F[i]);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
