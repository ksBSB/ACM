#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;
const int N = 1e4+5;
const int M = 6;
const int INF = 0x3f3f3f3f;

int n, dp[N][M+5];
vector<int> g[N];

bool get () {

	char s[N*M];
	gets(s);

	if (s[0] == '\0') return false;

	int len = strlen(s), i = 0;

	int u = -1, v = -1;
	while (s[i] < '0' && s[i] > '9') i++;

	for (; s[i] != ':'; i++) {
		if (u == -1) u = s[i] - '0';
		else u = u * 10 + s[i] - '0';
	}

	for (; i <= len; i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			if (v == -1) v = s[i] - '0';
			else v = v * 10 + s[i] - '0';
		} else {
			if (v != -1) {
				g[u].push_back(v);
				g[v].push_back(u);
				v = -1;
			}
		}
	}

	return true;
}

void dfs (int u, int f) {
	for (int i = 1; i <= M; i++)
		dp[u][i] = i;

	for (int i = 0; i < g[u].size(); i++) {

		int v = g[u][i];
		if (v == f) continue;

		dfs(v, u);

		for (int x = 1; x <= M; x++) {
			int cur = INF;
			for (int y = 1; y <= M; y++) {
				if (x == y) continue;
				cur = min(cur, dp[v][y]);
			}
			dp[u][x] += cur;
		}
	}
}

int main () {
	while (scanf("%d%*c", &n), n) {
		for (int i = 0; i < n; i++)
			g[i].clear();

		while (get()) ;

		dfs(0, -1);
		int ans = INF;
		for (int i = 1; i <= M; i++)
			ans = min(ans, dp[0][i]);
		printf("%d\n", ans);
	}
	return 0;
}
