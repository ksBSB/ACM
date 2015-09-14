#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;
const int maxn = 205;
const int maxm = 20005;

struct Edge {
	int u, v, d;
	bool operator < (const Edge& a) const { return d > a.d; }
}E[maxm];

char S[maxn], T[maxn];
int N, M, K, F[maxn];
map<string, int> G;

int find(int x) { return x == F[x] ? x : F[x] = find(F[x]); }
int ID(char* s) { if (!G.count(s)) G[s] = K++; return G[s]; }

void init () {
	K = 0;
	G.clear();
	for (int i = 0; i < N; i++) F[i] = i;

	for (int i = 0; i < M; i++) {
		scanf("%s%s%d", S, T, &E[i].d);
		E[i].u = ID(S);
		E[i].v = ID(T);
	}
	sort(E, E + M);
}

void solve () {
	scanf("%s%s", S, T);
	int s = G[S], t = G[T];
	for (int i = 0; i < M; i++) {
		int u = E[i].u, v = E[i].v;
		if (find(u) != find(v))
			F[find(u)] = find(v);
		if (find(s) == find(t)) {
			printf("%d tons\n\n", E[i].d);
			break;
		}
	}
}

int main () {
	int cas = 1;
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		printf("Scenario #%d\n", cas++);
		solve();
	}
	return 0;
}
