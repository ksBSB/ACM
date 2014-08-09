#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 3 * 1e5 + 5;
int N, M, Q, f[maxn], s[maxn];
int root, ans, rec;
vector<int> g[maxn];

int getfar(int x) {
	return f[x] == x ? x : f[x] = getfar(f[x]);
}

void link (int u, int v) {
	int x = getfar(u);
	int y = getfar(v);

	if (x == y)
		return;

	if (s[x] < s[y])
		swap(s[x], s[y]);

	f[y] = x;
	s[x] = max(s[x], (s[x] + 1) / 2 + (s[y] + 1) / 2 + 1);
}

void dfs (int u, int p, int d) {
	f[u] = root;

	if (d > ans) {
		ans = d;
		rec = u;
	}

	for (int i = 0; i < g[u].size(); i++) {
		if (g[u][i] != p)
			dfs(g[u][i], u, d+1);
	}
}

int main () {
	int type, u, v;

	scanf("%d%d%d", &N, &M, &Q);
	for (int i = 1; i <= N; i++) {
		f[i] = i;
		g[i].clear();
	}

	for (int i = 0; i < M; i++) {
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}

	for (int i = 1; i <= N; i++) {
		if (f[i] == i) {
			root = rec = i;
			ans = -1;
			dfs(i, 0, 0);

			ans = -1;
			dfs(rec, 0, 0);
			s[i] = ans;
		}
	}

	for (int i = 0; i < Q; i++) {
		scanf("%d", &type);
		if (type == 1) {
			scanf("%d", &u);
			v = getfar(u);
			printf("%d\n", s[v]);
		} else {
			scanf("%d%d", &u, &v);
			link(u, v);
		}
	}
	return 0;
}
