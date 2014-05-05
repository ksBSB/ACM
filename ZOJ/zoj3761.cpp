#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 2005;
const char sign[4][10] = { "UP", "DOWN", "LEFT", "RIGHT" };
struct point {
	int x, y, id;;
}s[N], t[N];

int n, v[N], rec[N], dir[N], ans;
vector<int> g[N];

bool cmpX(const point& a, const point& b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

bool cmpY(const point& a, const point& b) {
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}

void init () {
	ans = 0;
	memset(v, 0, sizeof(v));
	for (int i = 0; i < n; i++) {
		g[i].clear();

		scanf("%d%d", &s[i].x, &s[i].y);
		s[i].id = i;
		t[i] = s[i];
	}

	sort(t, t + n, cmpX);
	for (int i = 1; i < n; i++) {
		if (t[i-1].x == t[i].x) {
			int p = t[i-1].id, q = t[i].id;
			g[p].push_back(q);
			g[q].push_back(p);
		}
	}

	sort(t, t + n, cmpY);
	for (int i = 1; i < n; i++) {
		if (t[i-1].y == t[i].y) {
			int p = t[i-1].id, q = t[i].id;
			g[p].push_back(q);
			g[q].push_back(p);
		}
	}
}

int link(int p, int q) {
	if (s[p].x == s[q].x) {
		return s[p].y > s[q].y ? 0 : 1;
	} else {
		return s[p].x < s[q].x ? 2 : 3;
	}
}

void dfs(int u, int d) {
	v[u] = 1;

	for (int i = 0; i < g[u].size(); i++) if (v[g[u][i]] == 0) {
		int k = link(u, g[u][i]);
		dfs(g[u][i], k);
	}

	rec[ans] = u;
	dir[ans] = d;
	ans++;
}

void solve () {

	for (int i = 0; i < n; i++) if (v[i] == 0) {
		v[i] = 1;
		for (int j = 0; j < g[i].size(); j++) if (v[g[i][j]] == 0) {
			int k = link(i, g[i][j]);
			dfs(g[i][j], k);
		}
	}

	printf("%d\n", n - ans);
	for (int i = 0; i < ans; i++) {
		int p = rec[i];
		printf("(%d, %d) %s\n", s[p].x, s[p].y, sign[dir[i]]);
	}
}

int main () {
	while (scanf("%d", &n) == 1) {
		init();
		solve();
	}
	return 0;
}
