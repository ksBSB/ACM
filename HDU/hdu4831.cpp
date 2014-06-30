#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
const int N = 100005;
const int INF = 0x3f3f3f3f;
int n, pos[N], g[N][2];

inline int dis (int a, int b) {
	return abs(pos[a]-pos[b]);
}

inline void cat (int x, int mv) {
	if (mv == n+1)
		return;

	int& tmp = g[x][0];

	if (tmp == 0 || dis(x, mv) < dis(x, tmp)) {
		g[x][0] = mv;
	} else if (dis(x, mv) == dis(x, tmp)) {
		g[x][1] = mv;
	}
}

void init () {
	scanf("%d", &n);
	memset(g, 0, sizeof(g));
	memset(pos, 0, sizeof(pos));

	int mv = 0, val;
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &pos[i], &val);

		if (val) {
			mv = i;
			g[i][0] = -1;
			g[i][1] = val;
		} else {
			g[i][0] = mv;
		}
	}

	mv = n+1;
	for (int i = n; i; i--) {
		if (g[i][0] < 0) {
			mv = i;
		} else {
			cat(i, mv);
		}
	}
}

int find (int x) {
	if (x == 0)
		return 0;

	if (g[x][0] < 0)
		return g[x][1];
	else
		return max(find(g[x][0]), find(g[x][1]));
}

int query (int k) {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (find(i) <= k)
			ans++;
	}
	return ans;
}

void solve () {
	int m, a, b;
	char str[5];
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%s", str);
		if (str[0] == 'Q') {
			scanf("%d", &a);
			printf("%d\n", query(a));
		} else {
			scanf("%d%d", &a, &b);
			g[a+1][1] = b;
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case #%d:\n", i);
		solve();
	}
	return 0;
}
