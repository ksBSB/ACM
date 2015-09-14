#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int maxn = 1e6 + 5;

int N, Q, C[maxn], W[maxn];
vector<pii> G[maxn];

void dfs (int u, int f, int w) {
	W[u] = w;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i].first;
		if (v == f) continue;
		dfs(v, u, w ^ G[u][i].second);
	}
}

void init () {
	scanf("%d", &N);
	memset(W, 0, sizeof(W));
	memset(C, 0, sizeof(C));
	for (int i = 1; i <= N; i++) G[i].clear();

	int u, v, w;
	for (int i = 1; i < N; i++) {
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(make_pair(v, w));
		G[v].push_back(make_pair(u, w));
	}
	dfs(1, 0, 0);
	for (int i = 1; i <= N; i++) C[W[i]]++;
	//C[0] += N;
}

int main () {
	int cas, s;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			ll ans = 0;
			scanf("%d", &s);
			for (int j = 1; j <= N; j++) {
				int w = W[j] ^ s;
				ans += C[w];
			}
			if (s == 0)
				ans += N;
			printf("%lld\n", ans / 2);
		}
	}
	return 0;
}
