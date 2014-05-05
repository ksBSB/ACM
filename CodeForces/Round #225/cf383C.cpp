#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 200005;

struct state {
	int l, r, v, d;
}node[N];

int n, m, cnt, bit[2][N*2];
vector<int> g[N];

void add (int x, int val, int *b) {
	while (x <= n * 2) {
		b[x] += val;
		x += (x & (-x));
	}
}

int get(int x, int *b) {
	int ans = 0;
	while (x > 0) {
		ans += b[x];
		x -= (x & (-x));
	}
	return ans;
}

void dfs(int c, int fa, int d) {
	node[c].l = cnt++; node[c].d = d;
	for (int i = 0; i < g[c].size(); i++) {
		if (g[c][i] == fa) continue;
		dfs(g[c][i], c, 1 - d);
	}
	node[c].r = cnt++;
}

void init () {
	cnt = 1;
	scanf("%d%d", &n, &m);
	memset(bit, 0, sizeof(bit));
	for (int i = 1; i <= n; i++) scanf("%d", &node[i].v);
	
	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1, -1, 0);
}

void solve () {
	int o, a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d", &o);
		if (o == 1) {
			scanf("%d%d", &a, &b);
			add(node[a].l, b, bit[node[a].d]);
			add(node[a].r + 1, -b, bit[node[a].d]);
		} else {
			scanf("%d", &a);
			printf("%d\n", node[a].v + get(node[a].l, bit[node[a].d]) - get(node[a].l, bit[1 - node[a].d]));
		}
	}
}

int main () {
	init ();
	solve ();
	return 0;
}
