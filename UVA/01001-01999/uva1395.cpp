#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 105;
const int inf = 0x3f3f3f3f;

struct Edge {
	int u, v, d;
	bool operator < (const Edge& a) const { return d < a.d; }
}E[maxn * maxn];

int N, M, F[maxn], ans;

int find(int x) { return x == F[x] ? x : F[x] = find(F[x]); }

int solve (int s) {
	int n = N;
	for (int i = 1; i <= N; i++) F[i] = i;

	for (int i = s; i < M; i++) {
		int u = E[i].u, v = E[i].v;
		if (E[i].d - E[s].d >= ans) break;
		if (find(u) != find(v)) {
			if (--n == 1) return E[i].d - E[s].d;
			F[find(u)] = find(v);
		}
	}
	return inf;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		for (int i = 0; i < M; i++)
			scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].d);
		sort(E, E + M);
		ans = inf;
		for (int i = 0; i <= M - N + 1; i++)
			ans = min(ans, solve(i));
		printf("%d\n", ans == inf ? -1 : ans);
	}
	return 0;
}
