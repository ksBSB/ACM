#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;

int N, Q, D[maxn];
vector<int> G[maxn];

void init () {
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; i++)
		G[i].clear();

	int u, v;
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
}

int solve () {
	queue<int> que;

	que.push(1);
	int u = 1;
	memset(D, -1, sizeof(D));
	D[u] = 0;

	while (!que.empty()) {
		u = que.front();
		que.pop();

		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if (D[v] != -1) continue;
			D[v] = D[u] + 1;
			que.push(v);
		}
	}

	que.push(u);
	memset(D, -1, sizeof(D));
	D[u] = 0;
	while (!que.empty()) {
		u = que.front();
		que.pop();

		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if (D[v] != -1) continue;
			D[v] = D[u] + 1;
			que.push(v);
		}
	}
	return D[u] + 1;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		int n = solve(), x;
		while (Q--) {
			scanf("%d", &x);
			if (x <= n) printf("%d\n", x-1);
			else printf("%d\n", n-1 + (x-n) * 2);
		}
	}
	return 0;
}
