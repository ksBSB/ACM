#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 105;
const int M = 1e4+10;
const int INF = 0x3f3f3f3f;

int n, m, k, h[M], d[M];
int gay[N][M][3], dis[N][M][3], dp[N][M][3];

void init () {
	n++;
	memset(gay, 0, sizeof(gay));
	memset(dis, 0, sizeof(dis));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &h[j]);
			gay[i][j][1] = gay[i][j-1][1] + h[j];
		}
		for (int j = m-1; j >= 0; j--)
			gay[i][j][2] = gay[i][j+1][2] + h[j+1];
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &d[j]);
			dis[i][j][1] = dis[i][j-1][1] + d[j];
		}
		for (int j = m-1; j >= 0; j--)
			dis[i][j][2] = dis[i][j+1][2] + d[j+1];
	}
}

int func(int i, int j, int o) {
	return gay[i][j][o] - dp[i-1][j][0];
}

int solve () {
	int ans = -INF;
	deque<int> que;

	for (int i = 1; i <= n; i++) {
		que.clear();
		for (int j = 0; j <= m; j++) {
			while (!que.empty() && dis[i][j][1] - dis[i][que.front()][1] > k) que.pop_front();
			while (!que.empty() && func(i, que.back(), 1) >= func(i, j, 1)) que.pop_back();
			que.push_back(j);
			dp[i][j][1] = gay[i][j][1] - func(i, que.front(), 1);
		}

		que.clear();
		for (int j = m; j >= 0; j--) {
			while (!que.empty() && dis[i][j][2] - dis[i][que.front()][2] > k) que.pop_front();
			while (!que.empty() && func(i, que.back(), 2) >= func(i, j, 2)) que.pop_back();
			que.push_back(j);
			dp[i][j][2] = gay[i][j][2] - func(i, que.front(), 2);
		}

		for (int j = 0; j <= m; j++)
			dp[i][j][0] = max(dp[i][j][1], dp[i][j][2]);
	}

	for (int i = 0; i <= m; i++)
		ans = max(ans, dp[n][i][0]);
	return ans;
}

int main () {
	while (scanf("%d%d%d", &n, &m, &k) == 3 && n + m + k) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
