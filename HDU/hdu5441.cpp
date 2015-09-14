#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

const int maxn = 20005;
const int maxm = 100005;
const int maxq = 5005;

struct Edge {
	int u, v, w;
	Edge(int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}
	bool operator < (const Edge& a) const { return w < a.w; }
}E[maxm], Q[maxq];

int N, M, K, F[maxn], S[maxn];
ll ans[maxn];

int find(int x) { return x == F[x] ? x : F[x] = find(F[x]); }

void init () {
	scanf("%d%d%d", &N, &M, &K);
	int u, v, w;
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &u, &v, &w);
		E[i] = Edge(u, v, w);
	}
	for (int i = 0; i < K; i++) {
		scanf("%d", &w);
		Q[i] = Edge(i, 0, w);
	}
	sort(E, E + M);
	sort(Q, Q + K);
}

void solve ()  {
	for (int i = 1; i <= N; i++)
		F[i] = i, S[i] = 1;

	int p = 0;
	ll ret = 0;
	for (int i = 0; i < K; i++) {
		while (p < M && E[p].w <= Q[i].w) {
			int u = E[p].u, v = E[p].v, w = E[p].w;
			if (find(u) != find(v)) {
				ret += 1LL * S[find(u)] * S[find(v)];
				S[find(v)] += S[find(u)];
				F[find(u)] = find(v);
			}
			p++;
		}

		ans[Q[i].u] = ret;
	}
	for (int i = 0; i < K; i++)
		printf("%lld\n", ans[i] * 2);
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
