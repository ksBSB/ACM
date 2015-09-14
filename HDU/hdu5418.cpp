#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 16 + 5;
const int maxm = (1<<16) + 5;
const int inf = 0x3f3f3f3f;
typedef pair<int,int> pii;

int N, M, dp[maxm][maxn], vis[maxm][maxn], dis[maxn][maxn];

void init () {
	int u, v, w;
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			dis[i][j] = (i == j ? 0 : inf);

	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &u, &v, &w);
		dis[u-1][v-1] = min(dis[u-1][v-1], w);
		dis[v-1][u-1] = min(dis[v-1][u-1], w);
	}
}

int solve () {
	//if (N == 1) return 0;

	int T = 1<<N;
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < T; j++) dp[j][i] = inf;
	dp[0][0] = 0;
	vis[0][0] = 1;

	queue<pii> que;
	que.push(make_pair(0, 0));
	while(!que.empty()) {
		int s = que.front().first;
		int u = que.front().second;
		que.pop();

		for (int i = 0; i < N; i++) {
			int ss = s | (1<<i);
			if (dp[ss][i] > dp[s][u] + dis[u][i]) {
				dp[ss][i] = dp[s][u] + dis[u][i];
				if (vis[ss][i] == 0) {
					vis[ss][i] = 1;
					que.push(make_pair(ss, i));
				}
			}
		}
	}
	return dp[T-1][0];
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		printf("%d\n", solve());
	}
	return 0;
}
