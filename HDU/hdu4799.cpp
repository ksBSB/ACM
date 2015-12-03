#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 50005;

int N, X[2], W[maxn], F[maxn], V[maxn];
vector<int> G[maxn];
int dp[maxn][2];

void init () {
	int u;
	for (int i = 0; i <= N; i++) G[i].clear();

	for (int i = 1; i <= N; i++) {
		scanf("%d%d%d%d", &W[i], &u, &F[i], &V[i]);
		if (V[i]) W[i] *= -1;
		G[u].push_back(i);
	}
}

int dfs(int u, int d) {

	d ^= F[u];
	if (d) W[u]  = - W[u];
	dp[u][0] = W[u];
	dp[u][1] = -W[u];

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		dfs(v, d);
		dp[u][0] += max(dp[v][0], dp[v][1] - X[F[v]]);
		dp[u][1] += max(dp[v][0] - X[F[v]], dp[v][1]);
	}

	return dp[u][0];
}

int main () {
	while (scanf("%d%d%d", &N, &X[0], &X[1]) == 3) {
		init();
		int ans = dfs(0, 0);
		if (ans < 0) printf("HAHAHAOMG\n");
		else printf("%d\n", ans);
	}
	return 0;
}
