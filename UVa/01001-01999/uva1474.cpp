#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 4005;
const ll INF = 1e17;

struct team {
	int d, id;
} s[N], p[N];

int n, m, path[N][N], ans[N];
ll dp[2][N];

bool cmp(const team& a, const team& b) {
	if (a.d != b.d) return a.d < b.d;
	return a.id < b.id;
}

void init () {
	for (int i = 1; i <= n; i++) {
		scanf("%d", &s[i].d);
		s[i].id = i;
	}

	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &p[i].d);
		p[i].id = i;
	}

	sort(s+1, s+n+1, cmp);
	sort(p+1, p+m+1, cmp);
}

ll solve () {
	for (int i = 1; i <= m; i++) dp[0][i] = INF;
	dp[0][0] = 0;
	
	for (int i = 1; i <= n; i++) {
		int u = i%2;
		int v = 1-u;
		for (int j = 0; j <= m; j++) dp[u][j] = INF;

		for (int j = 1; j <= m && j <= i; j++) {
			if (dp[v][j-1] < dp[v][j]) {
				dp[u][j] = dp[v][j-1] + abs(s[i].d - p[j].d);
				path[i][j] = 1;
			} else {
				dp[u][j] = dp[v][j] + abs(s[i].d - p[j].d);
				path[i][j] = 0;
			}
		}
	}
	return dp[n%2][m];
}

void put(int x, int y) {
	if (x == 0 || y == 0) return;
	ans[s[x].id] = p[y].id;
	put(x-1, y-path[x][y]);
}

int main () {
	while (scanf("%d", &n) == 1) {
		init ();
		printf("%lld\n", solve ());
		put(n, m);
		for (int i = 1; i < n; i++) printf("%d ", ans[i]);
		printf("%d\n", ans[n]);
	}
	return 0;
}
