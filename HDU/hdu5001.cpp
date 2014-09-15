#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 55;
const int maxm = 10005;

int N, M, D;
vector<int> g[maxn];
double dp[maxm][maxn];

void init () {
	scanf("%d%d%d", &N, &M, &D);
	for (int i = 0; i <= N; i++)
		g[i].clear();

	int x, y;
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &x, &y);
		g[x].push_back(y);
		g[y].push_back(x);
	}

	for (int i = 1; i <= N; i++)
		g[0].push_back(i);
}

double solve (int u) {
	double ret = 0;
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;

	for (int i = 0; i <= D; i++) {

		for (int j = 0; j <= N; j++) {
			if (u == j)
				continue;

			double p = 1.0 / g[j].size();
			for (int k = 0; k < g[j].size(); k++)
				dp[i+1][g[j][k]] += dp[i][j] * p;
		}
		ret += dp[i+1][u];
	}
	return 1.0 - ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		for (int i = 1; i <= N; i++)
			printf("%.10lf\n", solve(i));
	}
	return 0;
}
