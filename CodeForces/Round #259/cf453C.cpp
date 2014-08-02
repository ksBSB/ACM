#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;

int N, M, a, b, s;
int ans, rec[maxn*4];
int c[maxn], v[maxn];
vector<int> g[maxn];

void init () {
	ans = s = 0;
	scanf("%d%d", &N, &M);
	memset(v, 0, sizeof(v));

	for (int i = 0; i < M; i++) {
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	for (int i = 1; i <= N; i++) {
		scanf("%d", &c[i]);
		if (c[i])
			s = i;
	}
}

inline void set (int u) {
	c[u] ^= 1;
	rec[ans++] = u;
}

void dfs (int u) {
	set(u);
	v[u] = 1;

	for (int i = 0; i < g[u].size(); i++) {

		if (v[g[u][i]])
			continue;

		dfs(g[u][i]);
		set(u);

		if (c[g[u][i]]) {
			set(g[u][i]);
			set(u);
		}
	}
}

bool judge () {
	for (int i = 1; i <= N; i++)
		if (c[i])
			return false;
	return true;
}

int main () {
	init();
	dfs(s);
	if (c[s]) {
		c[s] = 0;
		ans--;
	}

	if (judge ()) {
		printf("%d\n", ans);
		if (ans) {
			printf("%d", rec[0]);
			for (int i = 1; i < ans; i++)
				printf(" %d", rec[i]);
			printf("\n");
		}
	} else
		printf("-1\n");
	return 0;
}
