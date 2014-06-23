#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1005;
const int M = 2005;

struct state {
	int id;
	int val;
}p[N];

int n, m, v[N], val[N];
vector<int> g[N];

inline bool cmp (const state& a, const state& b) {
	return a.val > b.val;
}

void init () {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &val[i]);
		p[i].id = i;
		p[i].val = val[i];
	}
	sort(p + 1, p + n + 1, cmp);
	
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
}

int main () {
	init();
	int ans = 0;
	memset(v, 0, sizeof(v));

	for (int i = 1; i <= n; i++) {
		int u = p[i].id;
		v[u] = 1;

		for (int j = 0; j < g[u].size(); j++) {
			int vi = g[u][j];

			if (v[vi])
				continue;

			ans += val[vi];
		}
	}
	printf("%d\n", ans);
	return 0;
}
