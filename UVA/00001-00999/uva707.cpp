#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 105;
const int dir[5][2] = {{0, 1}, {0, -1}, {0, 0}, {1, 0}, {-1, 0}};

int N, M, T, dp[maxn][maxn][maxn];

void init () {
	int n, t, L, X, R, Y;
	memset(dp, -1, sizeof(dp));
	scanf("%d", &n);
	while (n--) {
		scanf("%d%d%d%d%d", &t, &L, &X, &R, &Y);
		for (int i = L; i <= R; i++)
			for (int j = X; j <= Y; j++)
				dp[i][j][t] = 0;
	}
}

int dfs(int x, int y, int t) {
	int& ans = dp[x][y][t];
	if (ans != -1) return ans;
	if (T == t) return ans = 1;
	ans = 0;
	for (int i = 0; i < 5; i++) {
		int p = x + dir[i][0];
		int q = y + dir[i][1];
		if (p <= 0 || p > N || q <= 0 || q > M) continue;
		if (dfs(p, q, t + 1))
			ans = 1;
	}
	return ans;
}

vector<pii> ans[maxn];
int solve () {
	for (int t = 1; t <= T; t++) {
		ans[t].clear();
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				if (dp[i][j][t] == 1)
					ans[t].push_back(make_pair(i, j));
		if (ans[t].size() == 0) return 0;
	}
	bool flag = true;
	for (int i = 1; i <= T; i++) {
		if (ans[i].size() == 1) {
			printf("Time step %d: The robber has been at %d,%d.\n", i, ans[i][0].first, ans[i][0].second);
			flag = false;
		}
	}

	return flag ? 1 : 2;
}

int main () {
	int cas = 1;
	while (scanf("%d%d%d", &N, &M, &T) == 3 && N + M + T) {
		init ();
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				dfs(i, j, 1);
		printf("Robbery #%d:\n", cas++);
		int n = solve();
		if (n == 0) printf("The robber has escaped.\n");
		else if (n == 1) printf("Nothing known.\n");
		printf("\n");
	}
	return 0;
}
