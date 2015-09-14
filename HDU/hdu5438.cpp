#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e4 + 5;

int N, M, L[maxn], R[maxn], F[maxn], C[maxn], in[maxn], vi[maxn];
ll W[maxn];
vector<int> G[maxn];

int find (int x) { return x == F[x] ? x : F[x] = find(F[x]); }

void init () {
	scanf("%d%d", &N, &M);
	memset(in, 0, sizeof(in));
	memset(vi, 0, sizeof(vi));
	for (int i = 1; i <= N; i++) {
		G[i].clear();
		scanf("%lld", &W[i]);
	}

	int u, v;
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
		in[v]++, in[u]++;
		L[i] = u; R[i] = v;
	}
}

ll solve () {
	queue<int> Q;
	for (int i = 1; i <= N; i++) if (in[i] < 2) {
		vi[i] = 1;
		Q.push(i);
	}

	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if (vi[v]) continue;
			in[v]--;
			if (in[v] < 2) {
				vi[v] = 1;
				Q.push(v);
			}
		}
	}

	for (int i = 0; i <= N; i++)
		F[i] = i, C[i] = 1;

	for (int i = 0; i < M; i++) {
		int u = L[i], v = R[i];
		if (vi[u] || vi[v]) continue;

		if (find(u) != find(v)) {
			C[find(v)] += C[find(u)];
			W[find(v)] += W[find(u)];
			F[find(u)] = find(v);
		}
	}

	ll ans = 0;
	for (int i = 1; i <= N; i++) {
		if (vi[i] || F[i] != i) continue;
		if (C[i]&1)
			ans += W[i];
	}

	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%lld\n", solve());
	}
	return 0;
}
